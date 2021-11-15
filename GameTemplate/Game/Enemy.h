#pragma once

//���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"

//���N���X���g�����߂ɐ錾����
class ModelRender;

class Enemy : public IGameObject
{
public:	//�R���X�g���N�^���X
	Enemy();
	~Enemy();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//�A�j���[�V����
	enum AnimationEnum	//�A�j���[�V������enum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//�A�j���[�V�����N���b�v

private:	//�f�[�^�����o
	ModelRender* m_enemyModel = nullptr;
	CharacterController m_enemyCC;

	Vector3 m_position = { 00.0f,0.0f,0.0f };
};

