#pragma once

//���N���X���C���N���[�h����
#include "SkinModelRender.h"
#include "Name.h"

class Player : public IGameObject
{
public:	//�R���X�g���N�^���X
	Player();
	~Player();
	bool Start() override final;
	void Update() override final;

private:	//�A�j���[�V����
	enum AnimationEnum	//�A�j���[�V������enum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//�A�j���[�V�����N���b�v

private:
	SkinModelRender* m_playerModel = nullptr;
};

