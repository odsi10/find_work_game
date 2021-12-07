#pragma once

//���N���X���C���N���[�h����
#include <Model.h>

#include "ModelRender.h"
#include "Name.h"
//#include "physics/Physics.h"

// ���N���X���g�����߂ɐ錾����
class Model;

class BackGround : public IGameObject
{
public:	//�R���X�g���N�^���X
	BackGround();
	~BackGround();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//�f�[�^�����o
	ModelRender* m_backGroundModel = nullptr;	// ���f�������_���[
	//PhysicsStaticObject m_backGroundPSO;		// �ÓI�I�u�W�F�N�g�̃R���W����	
	
	Vector3 m_position = { 0,0,0 };				// �I�u�W�F�N�g�̈ʒu
};