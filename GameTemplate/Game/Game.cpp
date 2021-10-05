#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{
	m_playerModel = NewGO<SkinModelRender>(0);
	m_playerModel->Init(filePath::tkm::PlayerModel);
	m_playerModel->SetPosition({ 0.0f,50.0f,0.0f });
	m_playerModel->SetScale({ 0.5f,0.5f,0.5f });
	
	m_backGround = NewGO<SkinModelRender>(0);
	m_backGround->Init(filePath::tkm::BackGround);
	return true;
}

void Game::Update()
{
}