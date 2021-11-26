#pragma once

// 他クラスをインクルードする
#include <vector>
#include <Model.h>

#include "ModelRender.h"
#include "GaussianBlur.h"

// 他クラスを使うために宣言する
class GaussianBlur;

// GPU側で利用するシャドウ用の構造体を定義する
struct ShadowParam
{
	Matrix m_mLVP;		// ライトビュープロジェクション行列
	Vector3 m_lightPos;	// ライトカメラの座標
};

class ShadowMap
{
public:	//コンストラクタ諸々
	ShadowMap();
	~ShadowMap();
	bool Start();
	void Update();

public:
	/// <summary>
	/// 影モデルを初期化
	/// </summary>
	void Init();
	
	/// <summary>
	/// 影モデルを登録
	/// </summary>
	/// <param name="shdowModel"></param>
	void RegistModel(Model* shdowModel)
	{
		m_modelArray.push_back(shdowModel);
	}

	/// <summary>
	/// 影モデルを描画
	/// </summary>
	/// <param name="renderContext"></param>
	void Draw(RenderContext& renderContext);

private:
	/// <summary>
	/// シャドウマップのレンダリングターゲットの初期化
	/// </summary>
	void InitShadowRenderTarget();

	/// <summary>
	/// ガウシアンブラーの初期化
	/// </summary>
	void InitGaussianBlur();

public:
	/// <summary>
	/// ライトカメラのゲッター
	/// </summary>
	/// <returns>ライトカメラ</returns>
	Camera& GetLightCamera()
	{
		return m_lightCamera;
	}

	/// <summary>
	/// シャドウマップのレンダリングターゲットのゲッター
	/// </summary>
	/// <returns></returns>
	RenderTarget& GetShadowMapRenderTarget()	// &なしのクラスのコピーに注意！！！アドレスを渡そう
	{
		return m_shadowMapRenderTarget;
	}

private: //データメンバ
	Camera m_lightCamera;					// 影描画用のライトカメラを作成する

	GaussianBlur m_gaussianBlur;			// ガウシアンブラー

	std::vector<Model*> m_modelArray;		// 影モデルの登録

	RenderTarget m_shadowMapRenderTarget;	// シャドウマップ描画用のレンダリングターゲットを初期化する
};