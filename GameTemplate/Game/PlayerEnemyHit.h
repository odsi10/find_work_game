#pragma once

// 他クラスをインクルードする
#include "Player.h"
#include "Enemy.h"

// 他クラスを使うために宣言する
class Player;
class Enemy;

class PlayerEnemyHit : public IGameObject
{
public:
	PlayerEnemyHit();
	~PlayerEnemyHit();
	bool Start(ShadowMap* shadowMap)override final;
	void Update()override final;



public: // Get関数
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

