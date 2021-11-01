#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	DeleteGO(m_enemyModel);
}

bool Enemy::Start(ShadowMap& shadowMap)
{
	m_enemyModel = NewGO<ModelRender>(0);
	/*m_model->Seta(true);
	m_model->Setb(true);*/
	m_enemyModel->Init(filePath::tkm::UnityChan);
	m_enemyCC.Init(
		35.0f,
		75.0f,
		m_position
	);

	return true;
}

void Enemy::Update()
{
	m_enemyModel->SetPosition(m_position);
}