#pragma once

//���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"

class BackGround : public IGameObject
{
public:	//�R���X�g���N�^���X
	BackGround();
	~BackGround();
	bool Start() override final;
	void Update() override final;

private:	//�f�[�^�����o
	ModelRender* m_backGroundModel = nullptr;
};

