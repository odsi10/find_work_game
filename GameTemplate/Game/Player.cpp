#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_playerModel);
}

bool Player::Start(ShadowMap* shadowMap)
{
	// �A�j���[�V�����N���b�v�����[�h���A���[�v�Đ����邩���߂�
	// �ҋ@
	m_playerAnimation[Idle].Load(filePath::tka::Idle);
	m_playerAnimation[Idle].SetLoopFlag(true);
	// �O�i
	m_playerAnimation[MoveForward].Load(filePath::tka::MoveForward);
	m_playerAnimation[MoveForward].SetLoopFlag(true);
	// �O�i�p���[2�i��
	m_playerAnimation[MoveForwardSecondPower].Load(filePath::tka::MoveForwardSecondPower);
	m_playerAnimation[MoveForwardSecondPower].SetLoopFlag(true);
	// �O�i�p���[�R�i��
	m_playerAnimation[MoveForwardThirdPower].Load(filePath::tka::MoveForwardThirdPower);
	m_playerAnimation[MoveForwardThirdPower].SetLoopFlag(true);

	m_playerAnimation[KnockBack].Load(filePath::tka::KnockBack);
	m_playerAnimation[KnockBack].SetLoopFlag(false);

	// ���f���̃C���X�^���X���쐬
	m_playerModel = NewGO<ModelRender>(0);

	// ���f���̏�����
	m_playerModel->Init(filePath::tkm::PlayerModel, *shadowMap, enModelUpAxis::enModelUpAxisZ, m_playerAnimation, AnimationMax);

	// �A�j���[�V������Idle���Đ�����
	m_playerModel->PlayAnimation(Idle);	

	// �ʒu���w��
	m_playerModel->SetPosition(m_position);

	m_playerEnemyHit = FindGO<PlayerEnemyHit>(findName::PlayerEnemyHit);

	return true;
}

void Player::Update()
{
	Vector3 diff = m_position - g_vec3Zero;
	if (diff.Length() > 1150.0f && m_position.y > -450.0f)
	{
		m_position.y -= 50.0f;

		// �w�肵���ʒu�����f���ɓ`����
		m_playerModel->SetPosition(m_position);
	}
	if (m_playerEnemyHit->GetKnockBackRigidityFlag(false)==false) {
		Move();
		Rotation();
		Animation();	
	}
	else {
		// �w�肵���ʒu�����f���ɓ`����
		m_playerModel->SetPosition(m_position);
	}

	PowerRelease();

	//// �ʒu�̎w��
	//m_position += m_moveSpeed;
}