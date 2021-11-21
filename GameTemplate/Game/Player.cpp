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
	m_playerAnimation[MoveForward].Load(filePath::tka::MoveForward);

	//m_playerModel->SetShadowCasterMake(true);
	m_playerModel = NewGO<ModelRender>(0);
	/*m_model->Seta(true);
	m_model->Setb(true);*/
	//m_playerModel->SetInitSkeleton(true);
	m_playerModel->Init(filePath::tkm::PlayerModel, *shadowMap, enModelUpAxis::enModelUpAxisZ, m_playerAnimation, AnimationMax);
	m_playerCC.Init(
		45.0f,
		55.0f,
		m_position
	);

	m_playerModel->SetPosition(m_position);

	return true;
}

void Player::Update()
{
	Move();
	Rotation();
	/*if (g_pad[0]->IsPress(enButtonA)) {
		m_playerAnimation[MoveForward].SetLoopFlag(true);
	}*/
}

void Player::Move()
{
	m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed;
	m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed;

	m_position = m_playerCC.Execute(m_moveSpeed, 1.0f);
	m_moveSpeed.y -= 1.0f;
	m_playerModel->SetPosition(m_position);
}

void Player::Rotation()
{
	m_moveSpeed.x = g_pad[0]->GetLStickXF();
	m_moveSpeed.z = g_pad[0]->GetLStickYF();
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	m_angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(g_vec3AxisY, m_angle);
	m_qRot.SetRotationDeg(g_vec3AxisY, 180.0f);
	m_rotation.Multiply(m_qRot, m_rotation);

	m_playerModel->SetRotation(m_rotation);
}

void Player::Animation()
{
	
}