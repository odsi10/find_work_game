#pragma once

//���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "physics/Physics.h"

// ���N���X���g�����߂ɐ錾����
class ModelRender;
class ShadowMap;

class BackGround : public IGameObject
{
public:	//�R���X�g���N�^���X
	BackGround();
	~BackGround();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//�f�[�^�����o
	ModelRender* m_backGroundModel = nullptr;
	PhysicsStaticObject m_backGroundPSO;

	Vector3 m_position = { 0,0,0 };
};

