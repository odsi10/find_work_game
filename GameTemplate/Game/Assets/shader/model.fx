/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0)
{
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ディレクションライトのデータを受け取るための
//定数バッファを用意する
cbuffer DirectionLightCb : register(b1)
{
	float3 ligDirection;//ライトの方向
	float3 ligColor;	//ライトのカラー
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn
{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal   : NORMAL;
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn
{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	//ピクセルシェーダーへの入力にカメラ空間の法線を追加する
	float3 normalInView : TEXCOORD2;	//カメラ空間の法線。
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);			//法線マップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////

//////////
// 反射光の計算
//////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);						//Lambert拡散反射光
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);		//Phong鏡面反射光
//////////
// ライト別の計算
//////////
float3 CalcLigFromDirectionLight(SPSIn psIn);	//ディレクションライトによる反射光
float3 CalcLigFromPointLight(SPSIn psIn);		//ポイントライトによる反射光
float3 CalcLigFromSpotLight(SPSIn psIn);		//スポットライトによる反射光
float CalcLigFromRimLight(SPSIn psIn);			//リムライトによる反射光
float3 CalcLigFromHemiLight(SPSIn psIn);		//半球ライトによる反射光


float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv);


////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

//法線マップから法線を得る
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
	float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, uv, 0.0f).xyz;
	binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

	float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

	return newNormal;
}

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}

	//ここから下を書くっぽい

	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.normal = mul(m, vsIn.normal);//法線を回転させる。

	psIn.uv = vsIn.uv;

	//カメラ空間の法線を求める
	psIn.normalInView = mul(mView, psIn.normal);

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//ピクセルの法線とライトの方向の内積を計算する。
	float inner_product = dot(psIn.normal,ligDirection);
	//内積の結果に-１を乗算する。
	inner_product *= -1.0f;

	//内積の結果が0以下なら0にする。
	if (inner_product < 0.0f) {
		inner_product = 0.0f;
	}

	//ピクセルが受けている光を求める。
	float3 diffuseLig = ligColor * inner_product;

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	//最終出力カラーに光を乗算する。
	albedoColor.xyz *= diffuseLig;

	return albedoColor;
}
