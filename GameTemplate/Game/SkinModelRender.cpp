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

void SkinModelRender::Init(const char* filePath,
	enModelUpAxis::EnModelUpAxis modelUpAxis
)
{
	//tkmファイルのファイルパスを保持
	m_tkmFilePath = filePath;

	//モデルの初期化
	InitModel(filePath);

	//初期化完了
	m_finishInit = true;
}

void SkinModelRender::InitModel(const char* filePath,
	enModelUpAxis::EnModelUpAxis modelUpAxis
)
{
	//ライトの設定
	//ディレクションライトを初期化する。
	InitDirectionLight();
	//3Dモデルをロードするための情報を設定する
	ModelInitData modelInitData;
	
	//tkmファイルのファイルパスを設定
	modelInitData.m_tkmFilePath = filePath;
	
	//使用するシェーダーファイルパスを設定
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	//ライトの情報を定数バッファとしてディスクリプタヒープに
	//登録するためにモデルの初期化情報として渡す。
	modelInitData.m_expandConstantBuffer = &m_light;
	modelInitData.m_expandConstantBufferSize = sizeof(m_light);

	//初期化情報を使ってモデル表示処理を初期化する
	m_model.Init(modelInitData);
}

//////////////////////////////
// ライトごとの初期化
//////////////////////////////

void SkinModelRender::InitDirectionLight()
{
	//ライトは斜め上から当たっている。
	m_light.ligDirection.x = 1.0f;
	m_light.ligDirection.y = -1.0f;
	m_light.ligDirection.z = -1.0f;
	//正規化する。
	m_light.ligDirection.Normalize();
	//ライトのカラーの設定（ライトの強さ）
	m_light.ligColor.x = 1.5f;
	m_light.ligColor.y = 1.5f;
	m_light.ligColor.z = 1.5f;

	//視点の位置を設定
	m_light.eyePos = g_camera3D->GetPosition();
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