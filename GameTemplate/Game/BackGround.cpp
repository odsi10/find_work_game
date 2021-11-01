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
	/*m_model->Seta(true);
	m_model->Setb(true);*/
	m_backGroundModel = NewGO<ModelRender>(0);
	m_backGroundModel->Init(filePath::tkm::BackGround);

	//m_backGroundPSO.CreateFromModel();
	
	return true;
}

void BackGround::Update()
{
	/*m_position.x -= g_pad[0]->GetLStickXF();
	m_position.y -= g_pad[0]->GetLStickYF();

	m_backGroundModel->SetPosition(m_position);*/
}