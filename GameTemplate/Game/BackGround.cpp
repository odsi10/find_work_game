#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	m_backGroundModel = NewGO<ModelRender>(0);
	m_backGroundModel->Init(filePath::tkm::BackGround);
	
	return true;
}

void BackGround::Update()
{
}