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
	// ���f���̃C���X�^���X���쐬����
	m_enemyModel = NewGO<ModelRender>(0);

	// ���f��������������
	m_enemyModel->Init(filePath::tkm::EnemyModel,*shadowMap);

	return true;
}

void Enemy::Update()
{
	Vector3 diff = m_position - g_vec3Zero;
	if (diff.Length() > 1150.0f && m_position.y > -450.0f)
	{
		m_position.y -= 50.0f;

		// �w�肵���ʒu�����f���ɓ`����
		m_enemyModel->SetPosition(m_position);
	}
	// �ʒu�̍X�V
	m_enemyModel->SetPosition(m_position);
}