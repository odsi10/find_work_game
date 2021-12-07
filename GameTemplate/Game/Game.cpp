#include "stdafx.h"
#include "Game.h"

//他クラスをインクルードする
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "PlayerEnemyHit.h"

Game::Game()
{
}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_playerEnemyHit);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_enemy);
}

bool Game::Start(ShadowMap* shadowMap)
{
	// ステージ
	m_backGround = NewGO<BackGround>(priority::PriorityZero, findName::BackGround);

	// プレイヤーと敵が当たったときの吹っ飛ばし処理
	m_playerEnemyHit = NewGO<PlayerEnemyHit>(priority::PriorityZero,findName::PlayerEnemyHit);

	// プレイヤー
	m_player = NewGO<Player>(priority::PriorityZero,findName::Player);

	// ゲームカメラ
	m_gameCamera = NewGO<GameCamera>(priority::PriorityZero, findName::GameCamera);

	// エネミー
	m_enemy = NewGO<Enemy>(priority::PriorityZero, findName::Enemy);

	return true;
}

void Game::Update()
{
}