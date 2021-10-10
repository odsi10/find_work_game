#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
	//m_playerAnimation[moveForward].Load(filePath::tka::MoveForward);

	m_playerModel = NewGO<SkinModelRender>(0);
	m_playerModel->Init(filePath::tkm::UnityChan);
	/*m_playerModel->SetPosition({ 0.0f,50.0f,0.0f });
	m_playerModel->SetScale({ 0.5f,0.5f,0.5f });*/

	//m_playerModel->PlayAnimation(moveForward);

	return true;
}

void Player::Update()
{
}