#include "stdafx.h"
#include "Game.h"

//他クラスをインクルードする
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"

Game::Game()
{
}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_enemy);
}

bool Game::Start(ShadowMap& shadowMap)
{
	m_backGround = NewGO<BackGround>(priority::PriorityZero, findName::BackGround);

	m_player = NewGO<Player>(priority::PriorityZero,findName::Player);

	m_gameCamera = NewGO<GameCamera>(priority::PriorityZero, findName::GameCamera);

	m_enemy = NewGO<Enemy>(priority::PriorityZero, findName::Enemy);

	return true;
}

void Game::Update()
{
}