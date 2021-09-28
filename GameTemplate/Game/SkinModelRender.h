#pragma once

//他クラスをインクルードする
#include<Model.h>

#include"Name.h"

//ライト用の構造体を定義する。
struct Light {
	//ディレクションライト
	Vector3 ligDirection;	//ライトの方向
	//HLSL側の定数バッファのfloat3型の変数は
	//16の倍数のアドレスに配置されるため、
	//C++側にはパディングを埋めておく。
	float dirPad;
	Vector3 ligColor;	//ライトのカラー。

	//拡散反射
	//構造体に視点の位置を追加する
	Vector3 eyePos; //視点の位置
	float eyePad;

	//環境光
	Vector3 ambientLight;   // アンビエントライト
	float ambiPad;
};

class SkinModelRender : public IGameObject
{
public:	//コンストラクタ諸々
	SkinModelRender();
	~SkinModelRender();
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& renderContext) override final;

public:
	/**
	 * @brief 初期化関数
	 * @param filePath tkmファイルのファイルパス
	*/
	void Init(const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ
	);

private:
	/**
	 * @brief モデルの初期化
	 * @param filePath tkmファイルのファイルパス
	*/
	void InitModel(const char* filePath,
		enModelUpAxis::EnModelUpAxis = enModelUpAxis::enModelUpAxisZ
	);

	void InitDirectionLight(); //ディレクションライト
	void InitPointLight(); //ポイントライト
	void InitSpotLight(); //スポットライト
	void InitAmbientLight(); //環境光
	void InitHemiLight(); //半球ライト

private: //データメンバ
	Model m_model;

	const char* m_tkmFilePath = nullptr; //tkmファイルのファイルパス

	Light m_light;	//ライト

	Vector3 m_position = g_vec3Zero;			//位置
	Quaternion m_rotation = g_quatIdentity;		//回転
	Vector3 m_scale = g_vec3One;				//拡大

	bool m_finishInit = false; //初期化が終わったか
};