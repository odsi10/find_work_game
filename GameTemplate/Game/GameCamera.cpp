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
	m_player = FindGO<Player>(findName::Player);

	g_camera3D->SetNear(100);
	g_camera3D->SetFar(10000);

	return true;
}

void GameCamera::Update()
{
	m_target = m_player->GetPosition();

	m_target.y += 50.0f;

	m_position = m_target;

	//m_position.x -= 1000.0f;
	m_position.y += 100.0f;
	m_position.z += 250.0f;

	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_position);

}
