#include "stdafx.h"
#include "Player.h"

// Player�w�b�_�[���g�p���Ă���

void Player::Move()
{
	// �d��
	m_moveSpeed.y -= 1.0f;
	
	// A�{�^����������Ă��Ȃ��Ƃ�
	if (!g_pad[0]->IsPress(enButtonA) && m_powerFlag == false) {
		// �A�i���O�X�e�B�b�N�̌X������擾���āA��b�ړ��ʂ�������
		m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed;
		m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed;
	}
	else if(m_playerCC.IsOnGround())
	{
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_powerFlag = true;
		// �p���[�^�C�}�[��60.0f��菬�����Ƃ�
		if (m_powerTimer < 60.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// �A�i���O�X�e�B�b�N�̌X�����擾
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed;
		}
		// �p���[�^�C�}�[��60.0f���傫�����A120.0f��菬�����Ƃ�
		else if (m_powerTimer > 60.0f && m_powerTimer < 120.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// �A�i���O�X�e�B�b�N�̌X�����擾
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed * 3;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed * 3;
		}
		// �p���[�^�C�}�[��120.0f���傫���Ƃ�
		else if (m_powerTimer > 120.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// �A�i���O�X�e�B�b�N�̌X�����擾
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed * 5;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed * 5;
		}
	}

	// �ʒu�̎w��
	m_position = m_playerCC.Execute(m_moveSpeed, 1.0f);

	// �w�肵���ʒu�����f���ɓ`����
	m_playerModel->SetPosition(m_position);
}

void Player::Rotation()
{
	// �A�i���O�X�e�B�b�N�̌X�����擾
	const float moveForward = g_pad[0]->GetLStickXF();
	const float moveRight = g_pad[0]->GetLStickYF();
	//m_moveSpeed.x = g_pad[0]->GetLStickXF();
	//m_moveSpeed.z = g_pad[0]->GetLStickYF();
	// �X��������������ꍇ�͖�������
	if (fabsf(moveForward) < 0.001f
		&& fabsf(moveRight) < 0.001f) {
		return;
	}
	// �A�[�N�^���W�F���g���g���Ēl������o��
	m_angle = atan2(moveForward, moveRight);
	// ������̉�]�N�H�[�^�j�I�����쐬
	m_rotation.SetRotation(g_vec3AxisY, m_angle);
	// ������̉�]�N�H�[�^�j�I�����쐬
	m_qRot.SetRotationDeg(g_vec3AxisY, 180.0f);
	// �N�H�[�^�j�I�����m�̏�Z
	m_rotation.Multiply(m_qRot, m_rotation);

	// ���߂���]�����f���ɓ`����
	m_playerModel->SetRotation(m_rotation);
}

void Player::Animation()
{
	// �A�i���O�X�e�B�b�N�̌X�����m�F���ꂽ���n�ʂ̂����ɂ���Ƃ�
	if (!g_pad[0]->IsPress(enButtonA) && g_pad[0]->GetLStickXF() != 0 && m_playerCC.IsOnGround()
		|| !g_pad[0]->IsPress(enButtonA) && g_pad[0]->GetLStickYF() != 0 && m_playerCC.IsOnGround() 
		|| g_pad[0]->IsPress(enButtonA))
	{
		// �p���[�^�C�}�[��60.0f��菬�����Ƃ�
		if (m_powerTimer < 60.0f)
		{
			// �O�i�̃A�j���[�V�����𗬂�
			m_playerModel->PlayAnimation(MoveForward);
		}
		// �p���[�^�C�}�[��60.0f���傫�����A120.0f��菬�����Ƃ�
		else if (m_powerTimer > 60.0f && m_powerTimer < 120.0f)
		{
			// �O�i�p���[2�i�ڂ̃A�j���[�V�������Đ�����
			m_playerModel->PlayAnimation(MoveForwardSecondPower);
		}
		// �p���[�^�C�}�[��120.0f���傫���Ƃ�
		else if (m_powerTimer > 120.0f && m_playerCC.IsOnGround())
		{
			// �O�i�p���[3�i�ڂ̃A�j���[�V�������Đ�����
			m_playerModel->PlayAnimation(MoveForwardThirdPower);
		}
	}
	// �Ȃɂ�����Ă��Ȃ��Ƃ�
	else
	{
		// �ҋ@�A�j���[�V�������Đ�����
		m_playerModel->PlayAnimation(Idle);
	}
}

void Player::PowerRelease()
{
	// A�{�^����������Ă���Ƃ�
	if (g_pad[0]->IsPress(enButtonA) && m_powerReleaseFlag == false)
	{
		// �p���[�^�C�}�[�n���I
		m_powerTimer++;
	}
	else if (!g_pad[0]->IsPress(enButtonA) && m_powerTimer > 0.0f && g_pad[0]->GetLStickXF() != 0
		|| !g_pad[0]->IsPress(enButtonA) && m_powerTimer > 0.0f && g_pad[0]->GetLStickYF() != 0)
	{
		m_powerReleaseFlag = true;
		m_powerReleaseTimer++;
		if (m_powerReleaseTimer == 60.0f)
		{
			m_powerFlag = false;
			m_powerTimer = 0.0f;
			m_powerReleaseTimer = 0.0f;
			m_powerReleaseFlag = false;
		}
	}
	else {
		m_powerFlag = false;
		m_powerTimer = 0.0f;
		m_powerReleaseTimer = 0.0f;
		m_powerReleaseFlag = false;
	}
}