
// プレイヤーと敵が当たったときの吹っ飛ばし処理

#include "stdafx.h"
#include "PlayerEnemyHit.h"

PlayerEnemyHit::PlayerEnemyHit()
{
}

PlayerEnemyHit::~PlayerEnemyHit()
{
}

bool PlayerEnemyHit::Start(ShadowMap* shadowMap)
{
	m_player = FindGO<Player>(findName::Player);

	m_enemy = FindGO<Enemy>(findName::Enemy);

	return true;
}

void PlayerEnemyHit::Update()
{
	Vector3 playerEnemyHit = m_enemy->GetPosition() - m_player->GetPosition();

	if (playerEnemyHit.Length() < 140.0f && m_knockBackRigidityFlag == false)
	{
		m_knockBackRigidityFlag = true;
	}
	else if (m_knockBackRigidityFlag == true)
	{
		Vector3 collisionEPower, collisionPPower;
		// プレイヤーが敵にぶつかった時のプレイヤーの前向きのベクトルを取得
		collisionEPower = m_player->GetMove();
		// 正規化して大きさ１にする
		collisionEPower.Normalize();
		switch (m_player->GetPower())
		{
		case 1:
			collisionEPower *= 0;
			break;
		case 2:
			collisionEPower *= 20.0f;
			break;
		case 3:
			collisionEPower *= 30.0f;
			break;
		default:
			break;
		}

		collisionPPower = collisionEPower;
		Vector3 enemyPosition;
		enemyPosition = m_enemy->GetPosition();
		Vector3 playerPosition;
		playerPosition = m_player->GetPosition();
		m_knockBackRigidityTimer++;
		if (m_knockBackRigidityTimer < 10.0f) {
			enemyPosition += collisionEPower;
			m_enemy->SetPosition(enemyPosition);
			playerPosition -= collisionPPower;
			m_player->SetPosition(playerPosition);
		}
		if (m_knockBackRigidityTimer > 20.0f)
		{
			m_player->SetPower(constants::IntOne);
			m_knockBackRigidityTimer = 0.0f;
			m_player->SetReleaseTimer(60.0f);
			m_knockBackRigidityFlag = false;
		}
	}
}