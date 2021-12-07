#pragma once

// 他クラスをインクルードする
#include <vector>
#include <Model.h>

#include "ModelRender.h"
#include "GaussianBlur.h"
#include "Player.h"

// 他クラスを使うために宣言する
class GaussianBlur;
class Player;

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

	RenderTarget m_shadowMapRenderTarget;	// シャドウマップ描画用のレンダリングターゲットを初期化する

	Player* m_player = nullptr;

	std::vector<Model*> m_modelArray;		// 影モデルの登録

	Vector3 m_lightCaneraPosition = { 1000,1000,1000 };
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };		 // 移動量
	float m_fSpeed = -6.0f;							 // 基礎移動量
};