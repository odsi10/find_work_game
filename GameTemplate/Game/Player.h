#pragma once

//���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"
#include "ShadowMap.h"
#include "ModelRender.h"

class ShadowMap;
class ModelRender;

class Player : public IGameObject
{
public:	//�R���X�g���N�^���X
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public:	//Get�֐�
	const Vector3 GetPosition()
	{
		return m_position;
	}
	
private:	//�A�j���[�V����
	enum AnimationEnum	//�A�j���[�V������enum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//�A�j���[�V�����N���b�v

private:	// �ړ�����
	void Move();
	void Rotation();

private:	//�f�[�^�����o
	ModelRender* m_playerModel = nullptr;

	CharacterController m_playerCC;
	Vector3 m_position = { 0.0f,0.0f,0.0f };
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	float fSpeed = -6.0f;
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	float angle;
	Quaternion qRot;
};

