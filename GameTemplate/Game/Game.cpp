#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	m_playerModel = NewGO<SkinModelRender>(0);
	m_playerModel->Init(filePath::tkm::PlayerModel);
}

Game::~Game()
{
}

bool Game::Start()
{

	return true;
}

void Game::Update()
{
}