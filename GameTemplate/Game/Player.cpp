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

	// ���f���̃C���X�^���X���쐬
	m_playerModel = NewGO<ModelRender>(0);

	// �L�����N�^�[�R���g���[���[�̍쐬 (�����^�R���W����)
	m_playerModel->Init(filePath::tkm::PlayerModel, *shadowMap, enModelUpAxis::enModelUpAxisZ, m_playerAnimation, AnimationMax);
	m_playerCC.Init(
		45.0f,
		55.0f,
		m_position
	);

	// �A�j���[�V������Idle���Đ�����
	m_playerModel->PlayAnimation(Idle);	

	// �ʒu���w��
	m_playerModel->SetPosition(m_position);

	return true;
}

void Player::Update()	// �e�֐��̒��g��PlayerAction�ɏ����Ă���
{
	Move();
	Rotation();
	Animation();
	PowerRelease();
}