#pragma once

// ���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "ShadowMap.h"
#include "ModelRender.h"
#include "PlayerEnemyHit.h"

// ���N���X���g�����߂ɐ錾����
class ShadowMap;
class ModelRender;
class PlayerEnemyHit;

class Player : public IGameObject
{
public:	// �R���X�g���N�^���X
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

private:	// �ړ�����
	/// <summary>
	/// �ʒu�̈ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �v���C���[�̌���
	/// </summary>
	void Rotation();

	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void Animation();

	/// <summary>
	/// �p���[���o����
	/// </summary>
	void PowerRelease();

public:	// Set�֐�
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	void SetMove(const Vector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	void SetPower(const int power)
	{
		m_power = power;
	}

	void SetReleaseTimer(const float releaseTimer)
	{
		m_powerReleaseTimer = releaseTimer;
	}

public:	// Get�֐�
	const Vector3& GetPosition()
	{
		return m_position;
	}

	const Vector3& GetMove()
	{
		return m_moveSpeed;
	}

	const int& GetPower()
	{
		return m_power;
	}

private:	// �A�j���[�V����
	enum AnimationEnum	// �A�j���[�V������enum
	{
		Idle,
		MoveForward,
		MoveForwardSecondPower,
		MoveForwardThirdPower,
		KnockBack,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//�A�j���[�V�����N���b�v

private:	// �f�[�^�����o
	ModelRender* m_playerModel = nullptr;	// ���f�������_���[
	PlayerEnemyHit* m_playerEnemyHit = nullptr;

	Vector3 m_position = { 0.0f,0.0f,1000.0f };		 // �v���C���[�̈ʒu
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };		 // �ړ���
	float m_fSpeed = -6.0f;							 // ��b�ړ���
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f }; // ��]
	float m_angle;									 // ��]	
	Quaternion m_qRot;								 // ��]

	float m_powerTimer = 0.0f;	// �p���[�����߂Ă��鎞�Ԃ��͂���^�C�}�[
	bool m_powerFlag = false;
	float m_powerReleaseTimer = 0.0f;
	bool m_powerReleaseFlag = false;
	int m_power = 0;
};