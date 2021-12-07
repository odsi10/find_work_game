#pragma once

// ���N���X���C���N���[�h����
#include "Player.h"
#include "Enemy.h"

// ���N���X���g�����߂ɐ錾����
class Player;
class Enemy;

class PlayerEnemyHit : public IGameObject
{
public:
	PlayerEnemyHit();
	~PlayerEnemyHit();
	bool Start(ShadowMap* shadowMap)override final;
	void Update()override final;



public: // Get�֐�
	const bool GetKnockBackRigidityFlag(const bool knockBackFlag)
	{
		return m_knockBackRigidityFlag;
	}

private:
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;

	bool m_knockBackRigidityFlag = false;
	float m_knockBackRigidityTimer = 0.0f;
};

