#include "stdafx.h"
#include "BackGround.h"
#include "ShadowMap.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
	DeleteGO(m_backGroundModel);
}

bool BackGround::Start(ShadowMap* shadowMap)
{
	// ���f�������_���[�̃C���X�^���X���쐬
	m_backGroundModel = NewGO<ModelRender>(0);

	// ���f���̏�����
	m_backGroundModel->Init(filePath::tkm::BackGround,*shadowMap);

	//// �ÓI�I�u�W�F�N�g�̃R���W�������쐬 (����͋����ɂ���ăv���C���[�Ȃǂ𐧌䂷�邽�߁A�g��Ȃ��j
	//m_backGroundPSO.CreateFromModel(m_backGroundModel->GetModel(), m_backGroundModel->GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{
}