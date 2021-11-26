#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_playerModel);
}

bool Player::Start(ShadowMap* shadowMap)
{
	// アニメーションクリップをロードし、ループ再生するか決める
	// 待機
	m_playerAnimation[Idle].Load(filePath::tka::Idle);
	m_playerAnimation[Idle].SetLoopFlag(true);
	// 前進
	m_playerAnimation[MoveForward].Load(filePath::tka::MoveForward);
	m_playerAnimation[MoveForward].SetLoopFlag(true);
	// 前進パワー2段目
	m_playerAnimation[MoveForwardSecondPower].Load(filePath::tka::MoveForwardSecondPower);
	m_playerAnimation[MoveForwardSecondPower].SetLoopFlag(true);
	// 前進パワー３段目
	m_playerAnimation[MoveForwardThirdPower].Load(filePath::tka::MoveForwardThirdPower);
	m_playerAnimation[MoveForwardThirdPower].SetLoopFlag(true);

	// モデルのインスタンスを作成
	m_playerModel = NewGO<ModelRender>(0);

	// キャラクターコントローラーの作成 (かご型コリジョン)
	m_playerModel->Init(filePath::tkm::PlayerModel, *shadowMap, enModelUpAxis::enModelUpAxisZ, m_playerAnimation, AnimationMax);
	m_playerCC.Init(
		45.0f,
		55.0f,
		m_position
	);

	// アニメーションのIdleを再生する
	m_playerModel->PlayAnimation(Idle);	

	// 位置を指定
	m_playerModel->SetPosition(m_position);

	return true;
}

void Player::Update()	// 各関数の中身はPlayerActionに書いてある
{
	Move();
	Rotation();
	Animation();
	PowerRelease();
}