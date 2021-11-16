#pragma once

// 他クラスをインクルードする
#include <vector>
#include <Model.h>

#include "ModelRender.h"
#include "GaussianBlur.h"

// 他クラスを使うために宣言する
class ModelRender;
class GaussianBlur;

class ShadowMap
{
public:
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
	Camera& GetLightCamera()
	{
		return m_lightCamera;
	}

	RenderTarget& GetRenderTarget()	//コピーに注意！！！
	{
		return m_shadowMapRenderTarget;
	}

private: //データメンバ
	ModelRender* m_modelRender = nullptr;

	// 影描画用のライトカメラを作成する
	Camera m_lightCamera;

	GaussianBlur m_gaussianBlur;

	std::vector<Model*> m_modelArray;

	RenderTarget m_shadowMapRenderTarget;	//シャドウマップ描画用のレンダリングターゲットを初期化する[
};