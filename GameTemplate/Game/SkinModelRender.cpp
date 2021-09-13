#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{
}

SkinModelRender::~SkinModelRender()
{
}

bool SkinModelRender::Start()
{
	return true;
}

void SkinModelRender::Init(const char* filePath)
{
	//tkmファイルのファイルパスを保持
	m_tkmFilePath = filePath;

	//モデルの初期化
	InitModel(filePath);

	//初期化完了
	m_finishInit = true;
}

void SkinModelRender::InitModel(const char* filePath)
{

	//3Dモデルをロードするための情報を設定する
	ModelInitData modelInitData;
	//tkmファイルのファイルパスを設定
	modelInitData.m_tkmFilePath = filePath;
	//使用するシェーダーファイルパスを設定
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	//初期化情報を使ってモデル表示処理を初期化する
	m_model.Init(modelInitData);
}

////////////////////////////////////////////////////////////
// 描画処理
////////////////////////////////////////////////////////////

void SkinModelRender::Render(RenderContext& renderContext)
{
	//未初期化時
	if (m_finishInit == false) {
		return;
	}

	//モデルの描画
	m_model.Draw(renderContext);
}

void SkinModelRender::Update()
{
	//未初期化時
	if (m_finishInit == false) {
		return;
	}

	//モデルの座標更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}