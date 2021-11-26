#include "stdafx.h"
#include "Game.h"

//���N���X���C���N���[�h����
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

bool Game::Start(ShadowMap* shadowMap)
{
	// �X�e�[�W
	m_backGround = NewGO<BackGround>(priority::PriorityZero, findName::BackGround);

	// �v���C���[
	m_player = NewGO<Player>(priority::PriorityZero,findName::Player);

	// �Q�[���J����
	m_gameCamera = NewGO<GameCamera>(priority::PriorityZero, findName::GameCamera);

	// �G�l�~�[
	m_enemy = NewGO<Enemy>(priority::PriorityZero, findName::Enemy);

	return true;
}

void Game::Update()
{
}