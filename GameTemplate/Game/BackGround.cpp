#include "stdafx.h"
#include "BackGround.h"
#include "ShadowMap.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
	DeleteGO(m_backGroundModel);
}

bool BackGround::Start(ShadowMap* shadowMap)
{
	// モデルレンダラーのインスタンスを作成
	m_backGroundModel = NewGO<ModelRender>(0);

	// モデルの初期化
	m_backGroundModel->Init(filePath::tkm::BackGround,*shadowMap);

	//// 静的オブジェクトのコリジョンを作成 (今回は距離によってプレイヤーなどを制御するため、使わない）
	//m_backGroundPSO.CreateFromModel(m_backGroundModel->GetModel(), m_backGroundModel->GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{
}