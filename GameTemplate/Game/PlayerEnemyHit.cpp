
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

	if (playerEnemyHit.Length() < 120.0f && m_knockBackRigidityFlag == false)
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
		// 吹っ飛ばす距離を指定
		collisionEPower *= 30;
		collisionPPower = collisionEPower;
		Vector3 playerPosition;
		playerPosition = m_player->GetPosition();
		Vector3 enemyPosition;
		enemyPosition = m_enemy->GetPosition();
		m_knockBackRigidityTimer++;
		if (m_knockBackRigidityTimer < 10) {
			enemyPosition += collisionEPower;
			m_enemy->SetPosition(enemyPosition);
			playerPosition -= collisionPPower;
			m_player->SetPosition(playerPosition);
		}
		if (m_knockBackRigidityTimer > 100.0f)
		{
			m_knockBackRigidityTimer = 0.0f;
			m_knockBackRigidityFlag = false;
		}
	}
}