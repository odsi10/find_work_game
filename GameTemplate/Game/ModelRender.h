#pragma once
// 他クラスをインクルードする
#include <Model.h>

//他のクラスをインクルードする
#include "Name.h"
#include "ShadowMap.h"

// 他クラスを使うために宣言する
class ShadowMap;

const int NUM_DIRECTIONAL_LIGHT = 4; // ディレクションライトの数

//ライト用の構造体を定義する
struct Light {
	//ディレクションライト
	Vector3 dirDirection; //ライトの方向
	//HLSL側の定数バッファのfloat3型の変数は16の倍数のアドレスに配置されるため、
	//C++側にはパディングを埋めておく。
	float dirPad;
	Vector3 dirColor;
	float colPad;

	//ポイントライト
	Vector3 ptPosition; //位置
	float ptPad;		//パディング
	Vector3 ptColor;	//カラー
	float ptRange;		//影響範囲

	//スポットライト
	Vector3 spPosition;		//位置
	float spPad;			//パディング
	Vector3 spColor;		//カラー
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度

	//構造体に視点の位置を追加する
	Vector3 eyePos; //視点の位置
	float eyePad;   //パディング

	//環境光
	Vector3 ambientLight;   // アンビエントライト
	float ambPad;			//パディング

	//半球ライト
	Vector3 groundColor;	//地面色
	float groPad;			//パディング
	Vector3 skyColor;		//天球色
	float skyPad;			//パディング
	Vector3 groundNormal;	//地面の法線
};



class ModelRender : public IGameObject
{
public:
	ModelRender();
	~ModelRender();
	bool Start(ShadowMap& shadowMap) override final;
	void Update() override final;
	void Render(RenderContext& renderContext) override final;



public:
	/**
	 * @brief 初期化関数
	 * @param filePath tkmファイルのファイルパス
	*/
	//void Init(const char* filePath);


	void Init(const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ/*,
		AnimationClip* animationClip = nullptr,
		int maxAnimationClipNum = 0*/
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
	void InitPointLight();     //ポイントライト
	void InitSpotLight();      //スポットライト
	void InitAmbientLight();   //環境光
	void InitHemiLight();      //半球ライト

	bool InitSkeleton(const char* filePath);

	/**
	 * @brief アニメーションの初期化
	 * @param animationClip アニメーションクリップ
	 * @param maxAnimationClipNum アニメーションクリップの総数
	*/
	void InitAnimation(AnimationClip* animationClip, int maxAnimationClipNum);

	void InitShadowModel();

public:
	/**
	 * @brief アニメーションを再生する
	 * @param animationNumber 登録しているアニメーションクリップの番号
	 * @param interpolateTime 補完時間（単位：秒）
	*/
	void PlayAnimation(int animationNumber, float interpolateTime = 0.2f)
	{
		m_animationPointer->Play(animationNumber, interpolateTime);
	}

	/**
	 * @brief アニメーションを再生中か
	 * @return 再生中
	*/
	const bool IsPlayingAnimation() const
	{
		return m_animationPointer->IsPlaying();
	}

	bool IsInited() const
	{
		return m_animationPointer->IsInited();
	}



public: //Get関数

	const Vector3 GetPosition()
	{
		return m_position;
	}

	const Quaternion GetRotation()
	{
		return m_rotation;
	}

	const Vector3 GetScale()
	{
		return m_scale;
	}

	Model Getmodel()
	{
		m_ShadowModel;
	}

public: //Set関数

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	void UpPositionY(const float upY)
	{
		m_position.y += upY;
	}

	void DownPositionY(const float downY)
	{
		m_position.y -= downY;
	}

	void ResetPositionY()
	{
		m_position.y = 0.0f;
	}

	void SetRotation(const Quaternion rotation)
	{
		m_rotation = rotation;
	}

	void SetRotationX(const float rotX) {
		m_rotation.SetRotationX(rotX);
	}

	void SetRotationDegY(const float rotY) {
		m_rotation.SetRotationDegY(rotY);
	}

	void SetScale(const Vector3 scale)
	{
		m_scale = scale;
	}

private: //data menber
	Model m_model;	//モデル
	std::unique_ptr<Skeleton> m_skeletonPointer; //スケルトンのポインター
	std::unique_ptr<Animation> m_animationPointer; //アニメーションのポインター

	const char* m_tkmFilePath = nullptr; //tkmファイルのファイルパス
	Light m_light;						 //ライト

	Vector3 m_position = g_vec3Zero;			//位置
	Quaternion m_rotation = g_quatIdentity;		//回転
	Vector3 m_scale = g_vec3One;				//拡大

	bool m_finishInit = false; //初期化が終わったか

	ModelInitData m_shadowModelInitData; //シャドウマップに描画するモデルを初期化する
	Model m_ShadowModel;	//シャドウ用のモデルを初期化する

	ShadowMap* m_shadowMap = nullptr;
};