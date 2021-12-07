
// �v���C���[�ƓG�����������Ƃ��̐�����΂�����

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
		// �v���C���[���G�ɂԂ��������̃v���C���[�̑O�����̃x�N�g�����擾
		collisionEPower = m_player->GetMove();
		// ���K�����đ傫���P�ɂ���
		collisionEPower.Normalize();
		// ������΂��������w��
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