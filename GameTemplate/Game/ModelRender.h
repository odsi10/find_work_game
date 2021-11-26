#pragma once
// 他クラスをインクルードする
#include <Model.h>

#include "Name.h"
#include "ShadowMap.h"
#include "AnimationClip.h"

// 他クラスを使うために宣言する
class ShadowMap;
class AnimationClip;

//const int NUM_DIRECTIONAL_LIGHT = 4; // ディレクションライトの数

// ライト用の構造体を定義する
struct Light {
	// ディレクションライト
	Vector3 dirDirection; //ライトの方向
	// HLSL側の定数バッファのfloat3型の変数は16の倍数のアドレスに配置されるため、
	// C++側にはパディングを埋めておく。
	float dirPad;
	Vector3 dirColor;
	float colPad;

	// ポイントライト
	Vector3 ptPosition; //位置
	float ptPad;		//パディング
	Vector3 ptColor;	//カラー
	float ptRange;		//影響範囲

	// スポットライト
	Vector3 spPosition;		//位置
	float spPad;			//パディング
	Vector3 spColor;		//カラー
	float spRange;			//影響範囲
	Vector3 spDirection;	//射出方向
	float spAngle;			//射出角度

	// 構造体に視点の位置を追加する
	Vector3 eyePos; //視点の位置
	float eyePad;   //パディング

	// 環境光
	Vector3 ambientLight;   // アンビエントライト
	float ambPad;			//パディング

	// 半球ライト
	Vector3 groundColor;	//地面色
	float groPad;			//パディング
	Vector3 skyColor;		//天球色
	float skyPad;			//パディング
	Vector3 groundNormal;	//地面の法線
};



class ModelRender : public IGameObject
{
public:	// コンストラクタ諸々
	ModelRender();
	~ModelRender();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();
	void Render(RenderContext& renderContext) override final;

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="shadowMap">シャドウマップ</param>
	/// <param name="modelUpAxis">モデルの上方向</param>
	/// <param name="animationClip">アニメーションクリップ</param>
	/// <param name="maxAnimationClipNum">アニメーションクリップの総数</param>
	void Init(const char* filePath,
		ShadowMap& shadowMap,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ,
		AnimationClip * animationClip = nullptr,
		int maxAnimationClipNum = 0
	);

private:
	/// <summary>
	/// ディレクションライト
	/// </summary>
	void InitDirectionLight();
	/// <summary>
	/// ポイントライト
	/// </summary>
	void InitPointLight();
	/// <summary>
	/// スポットライト
	/// </summary>
	void InitSpotLight();
	/// <summary>
	/// 環境光
	/// </summary>
	void InitAmbientLight();
	/// <summary>
	/// 半球ライト
	/// </summary>
	void InitHemiLight();

	/// <summary>
	/// スケルトンの初期化
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <returns></returns>
	bool InitSkeleton(const char* filePath);

	/**
	 * @brief アニメーションの初期化
	 * @param animationClip アニメーションクリップ
	 * @param maxAnimationClipNum アニメーションクリップの総数
	*/
	void InitAnimation(AnimationClip* animationClip, int maxAnimationClipNum);

	/// <summary>
	/// シャドウの書き込み
	/// </summary>
	/// <param name="shadowMap">シャドウマップ</param>
	void InitShadowModel(ShadowMap* shadowMap);

	/// <summary>
	/// 影が落とされるモデルを初期化する（今回はすべて影が落とされるモデル）
	/// </summary>
	/// <param name="shadowMap">シャドウマップ</param>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="modelUpAxis">モデルの上方向</param>
	void InitShadowReceiver(
		ShadowMap* shadowMap,
		const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis
	);

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

public: // Get関数

	/// <summary>
	/// モデルの位置を取得できる
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// モデルの回転を取得できる
	/// </summary>
	/// <returns></returns>
	const Quaternion GetRotation()
	{
		return m_rotation;
	}

	/// <summary>
	/// モデルの拡大、縮小を取得できる
	/// </summary>
	/// <returns></returns>
	const Vector3 GetScale()
	{
		return m_scale;
	}

	/// <summary>
	/// モデルのアドレスを取得できる
	/// </summary>
	/// <returns></returns>
	Model& GetModel()
	{
		return m_model;
	}

	

public: // Set関数
	/// <summary>
	/// モデルの位置を指定できる
	/// </summary>
	/// <param name="position">位置</param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// モデルの回転を指定できる
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion rotation)
	{
		m_rotation = rotation;
	}

private: //	データメンバ
	Model m_model;						 // モデル
	ModelInitData m_modelInitData;		 // モデルの初期化するための情報を設定
	ModelInitData m_shadowModelInitData; // シャドウマップに描画するモデルを初期化する
	Model m_ShadowModel;				 // シャドウ用のモデルを初期化する
	ShadowMap* m_shadowMap = nullptr;	 // シャドウマップ
	Light m_light;						 // ライト

	std::unique_ptr<Skeleton> m_skeletonPointer;	// スケルトンのポインター
	std::unique_ptr<Animation> m_animationPointer;  // アニメーションのポインター

	Vector3 m_position = g_vec3Zero;			// 位置
	Quaternion m_rotation = g_quatIdentity;		// 回転
	Vector3 m_scale = g_vec3One;				// 拡大

	const char* m_tkmFilePath = nullptr; // tkmファイルのファイルパス
	
	bool m_initSkeleton = false;		 // スケルトンの初期化がされたか
	bool m_finishInit = false;			 // 初期化が終わったか
};