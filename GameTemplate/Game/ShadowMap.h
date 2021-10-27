#pragma once

// 他クラスをインクルードする
#include <vector>
#include <Model.h>

#include "ModelRender.h"

// 他クラスを使うために宣言する
class ModelRender;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	bool Start();
	void Update();

public:
	void Init();

	void Drow(RenderContext& renderContext);
	/// <summary>
	/// 影モデルを登録
	/// </summary>
	/// <param name="shdowModel"></param>
	void RegistModel(Model* shdowModel)
	{
		m_modelArray.push_back(shdowModel);
	}

	void AddModel(Model& ShadowModel);

private:
	void ShadowRenderTarget();

private: //データメンバ
	ModelRender* m_modelRender = nullptr;

	std::vector<Model*> m_modelArray;

	RenderTarget m_shadowMap;	//シャドウマップ描画用のレンダリングターゲットを初期化する
};