#pragma once

// ���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"
#include "ShadowMap.h"
#include "ModelRender.h"

// ���N���X���g�����߂ɐ錾����
class ShadowMap;
class ModelRender;

class Player : public IGameObject
{
public:	// �R���X�g���N�^���X
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public:	// Get�֐�
	const Vector3 GetPosition()
	{
		return m_position;
	}

private:	// �A�j���[�V����
	enum AnimationEnum	// �A�j���[�V������enum
	{
		Idle,
		MoveForward,
		MoveForwardSecondPower,
		MoveForwardThirdPower,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//�A�j���[�V�����N���b�v

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

private:	// �f�[�^�����o
	ModelRender* m_playerModel = nullptr;	// ���f�������_���[
	CharacterController m_playerCC;			// �L�����N�^�[�R���g���[���[

	Vector3 m_position = { 0.0f,0.0f,500.0f };		 // �v���C���[�̈ʒu
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };		 // �ړ���
	float m_fSpeed = -6.0f;							 // ��b�ړ���
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f }; // ��]
	float m_angle;									 // ��]	
	Quaternion m_qRot;								 // ��]

	float m_powerTimer = 0.0f;	// �p���[�����߂Ă��鎞�Ԃ��͂���^�C�}�[
	bool m_powerFlag = false;
	float m_powerReleaseTimer = 0.0f;
	bool m_powerReleaseFlag = false;
};