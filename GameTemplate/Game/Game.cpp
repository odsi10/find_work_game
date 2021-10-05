#include "stdafx.h"
#include "Game.h"

//他クラスをインクルードする
#include "Player.h"
#include "BackGround.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Start()
{	
	m_backGround = NewGO<BackGround>(0);

	m_player = NewGO<Player>(0);

	return true;
}

void Game::Update()
{
}