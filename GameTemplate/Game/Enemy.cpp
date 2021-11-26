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

	// �L�����N�^�[�R���g���[���[���쐬����
	m_enemyCC.Init(
		35.0f,
		75.0f,
		m_position
	);

	return true;
}

void Enemy::Update()
{
	// �ʒu�̍X�V
	m_enemyModel->SetPosition(m_position);
}