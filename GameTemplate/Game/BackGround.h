#pragma once

//���N���X���C���N���[�h����
#include "SkinModelRender.h"
#include "Name.h"

class BackGround : public IGameObject
{
public:	//�R���X�g���N�^���X
	BackGround();
	~BackGround();
	bool Start() override final;
	void Update() override final;

private:	//�f�[�^�����o
	SkinModelRender* m_backGroundModel = nullptr;
};

