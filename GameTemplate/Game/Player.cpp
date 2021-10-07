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
	m_playerModel->Init(filePath::tkm::PlayerModel);

	//m_playerModel->PlayAnimation(moveForward);

	return true;
}

void Player::Update()
{
}