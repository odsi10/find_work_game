#include "stdafx.h"
#include "GameCamera.h"

//他クラスをインクルードする
#include "Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start(ShadowMap* shadowMap)
{
	// プレイヤーを探す
	m_player = FindGO<Player>(findName::Player);

	// 近平面までの距離を設定
	g_camera3D->SetNear(100);
	// 遠平面までの距離を設定
	g_camera3D->SetFar(10000);

	return true;
}

void GameCamera::Update()
{
	// プレイヤーのポジションを取得
	m_target = m_player->GetPosition();

	// プレイヤーの少し上にする
	m_target.y += 50.0f;

	// ターゲットの値をカメラのポジションにいれる
	m_position = m_target;

	// ポジションをプレイヤーからいい感じに離す
	m_position.y += 100.0f;
	m_position.z += 250.0f;

	// カメラのターゲットを指定
	g_camera3D->SetTarget(m_target);
	// カメラのポジションを指定
	g_camera3D->SetPosition(m_position);
}
