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

	// キャラクターコントローラーを作成する
	m_enemyCC.Init(
		35.0f,
		75.0f,
		m_position
	);

	return true;
}

void Enemy::Update()
{
	// 位置の更新
	m_enemyModel->SetPosition(m_position);
}