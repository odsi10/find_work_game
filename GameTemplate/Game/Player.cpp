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

	m_playerAnimation[KnockBack].Load(filePath::tka::KnockBack);
	m_playerAnimation[KnockBack].SetLoopFlag(false);

	// モデルのインスタンスを作成
	m_playerModel = NewGO<ModelRender>(0);

	// モデルの初期化
	m_playerModel->Init(filePath::tkm::PlayerModel, *shadowMap, enModelUpAxis::enModelUpAxisZ, m_playerAnimation, AnimationMax);

	// アニメーションのIdleを再生する
	m_playerModel->PlayAnimation(Idle);	

	// 位置を指定
	m_playerModel->SetPosition(m_position);

	m_playerEnemyHit = FindGO<PlayerEnemyHit>(findName::PlayerEnemyHit);

	return true;
}

void Player::Update()
{
	Vector3 diff = m_position - g_vec3Zero;
	if (diff.Length() > 1150.0f && m_position.y > -450.0f)
	{
		m_position.y -= 50.0f;

		// 指定した位置をモデルに伝える
		m_playerModel->SetPosition(m_position);
	}
	if (m_playerEnemyHit->GetKnockBackRigidityFlag(false)==false) {
		Move();
		Rotation();
		Animation();	
	}
	else {
		// 指定した位置をモデルに伝える
		m_playerModel->SetPosition(m_position);
	}

	PowerRelease();

	//// 位置の指定
	//m_position += m_moveSpeed;
}