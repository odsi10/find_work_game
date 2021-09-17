#pragma once

//他クラスをインクルードする
#include<Model.h>

#include"Name.h"

//ライト用の構造体を定義する
struct Light {
	//ディレクションライト
	Vector3 dirDirection; //ライトの方向
	//C++側にはパディングを埋めておく。
	float pad;
	Vector3 dirColor;
	float dirPad;

	//ポイントライト
	Vector3 ptPosition; //位置
	float ptPad;			//パディング
	Vector3 ptColor;	//カラー
	float ptRange;		//影響範囲

	//スポットライト
	Vector3 spPosition;		//位置
	float spPad;				//パディング
	Vector3 spColor;		//カラー
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度

	//構造体に視点の位置を追加する
	Vector3 eyePos; //視点の位置
	float eyePad;

	//環境光
	Vector3 ambientLight;   // アンビエントライト
	float ambPad;

	//半球ライト
	Vector3 groundColor;	//地面色
	float groPad;
	Vector3 skyColor;		//天球色
	float skyPad;
	Vector3 groundNormal;	//地面の法線
};

class SkinModelRender : public IGameObject
{
public:
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

	Light m_light;

	Vector3 m_position = g_vec3Zero;			//位置
	Quaternion m_rotation = g_quatIdentity;		//回転
	Vector3 m_scale = g_vec3One;				//拡大

	bool m_finishInit = false; //初期化が終わったか
};