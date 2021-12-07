#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	DeleteGO(m_enemyModel);
}

bool Enemy::Start(ShadowMap* shadowMap)
{
	// モデルのインスタンスを作成する
	m_enemyModel = NewGO<ModelRender>(0);

	// モデルを初期化する
	m_enemyModel->Init(filePath::tkm::EnemyModel,*shadowMap);

	return true;
}

void Enemy::Update()
{
	Vector3 diff = m_position - g_vec3Zero;
	if (diff.Length() > 1150.0f && m_position.y > -450.0f)
	{
		m_position.y -= 50.0f;

		// 指定した位置をモデルに伝える
		m_enemyModel->SetPosition(m_position);
	}
	// 位置の更新
	m_enemyModel->SetPosition(m_position);
}