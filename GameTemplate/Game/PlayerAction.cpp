#include "stdafx.h"
#include "Player.h"

// Playerヘッダーを使用している

void Player::Move()
{
	// Aボタンが押されていないとき
	if (!g_pad[0]->IsPress(enButtonA) && m_powerFlag == false) {
		// アナログスティックの傾き具合を取得して、基礎移動量をかける
		m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed;
		m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed;
	}
	else {
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_powerFlag = true;
		// パワータイマーが60.0fより小さいとき
		if (m_powerTimer < 60.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// アナログスティックの傾きを取得
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed;
			m_power = constants::IntOne;
		}
		// パワータイマーが60.0fより大きいかつ、120.0fより小さいとき
		else if (m_powerTimer > 60.0f && m_powerTimer < 120.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// アナログスティックの傾きを取得
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed * 4;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed * 4;
			m_power = constants::IntTwo;
		}
		// パワータイマーが120.0fより大きいとき
		else if (m_powerTimer > 120.0f && m_powerFlag == true && !g_pad[0]->IsPress(enButtonA))
		{
			// アナログスティックの傾きを取得
			m_moveSpeed.x = g_pad[0]->GetLStickXF() * m_fSpeed * 7;
			m_moveSpeed.z = g_pad[0]->GetLStickYF() * m_fSpeed * 7;
			m_power = constants::IntThree;
		}
	}

	// 位置の指定
	m_position += m_moveSpeed;

	// 指定した位置をモデルに伝える
	m_playerModel->SetPosition(m_position);
}

void Player::Rotation()
{
	// アナログスティックの傾きを取得
	const float moveForward = g_pad[0]->GetLStickXF();
	const float moveRight = g_pad[0]->GetLStickYF();

	// 傾きが小さすぎる場合は無視する
	if (fabsf(moveForward) < 0.001f
		&& fabsf(moveRight) < 0.001f) {
		return;
	}
	// アークタンジェントを使って値を出す
	m_angle = atan2(moveForward, moveRight);
	// 軸周りの回転クォータニオンを作成
	m_rotation.SetRotation(g_vec3AxisY, m_angle);
	// 軸周りの回転クォータニオンを作成
	m_qRot.SetRotationDeg(g_vec3AxisY, 180.0f);
	// クォータニオン同士の乗算
	m_rotation.Multiply(m_qRot, m_rotation);

	// 求めた回転をモデルに伝える
	m_playerModel->SetRotation(m_rotation);
}

void Player::Animation()
{
	// アナログスティックの傾きが確認されたかつ地面のうえにいるとき
	if (!g_pad[0]->IsPress(enButtonA) && g_pad[0]->GetLStickXF() != 0
		|| !g_pad[0]->IsPress(enButtonA) && g_pad[0]->GetLStickYF() != 0
		|| g_pad[0]->IsPress(enButtonA))
	{
		// パワータイマーが60.0fより小さいとき
		if (m_powerTimer < 60.0f)
		{
			// 前進のアニメーションを流す
			m_playerModel->PlayAnimation(MoveForward);
		}
		// パワータイマーが60.0fより大きいかつ、120.0fより小さいとき
		else if (m_powerTimer > 60.0f && m_powerTimer < 120.0f)
		{
			// 前進パワー2段目のアニメーションを再生する
			m_playerModel->PlayAnimation(MoveForwardSecondPower);
		}
		// パワータイマーが120.0fより大きいとき
		else if (m_powerTimer > 120.0f)
		{
			// 前進パワー3段目のアニメーションを再生する
			m_playerModel->PlayAnimation(MoveForwardThirdPower);
		}
	}
	// なにもされていないとき
	else
	{
		// 待機アニメーションを再生する
		m_playerModel->PlayAnimation(Idle);
	}
}

void Player::PowerRelease()
{
	// Aボタンが押されているとき
	if (g_pad[0]->IsPress(enButtonA) && m_powerReleaseFlag == false)
	{
		// パワータイマー始動！
		m_powerTimer++;
	}
	else if (!g_pad[0]->IsPress(enButtonA) && m_powerTimer > 0.0f && g_pad[0]->GetLStickXF() != 0
		|| !g_pad[0]->IsPress(enButtonA) && m_powerTimer > 0.0f && g_pad[0]->GetLStickYF() != 0)
	{
		m_powerReleaseFlag = true;
		m_powerReleaseTimer++;
		if (m_powerReleaseTimer == 60.0f)
		{
			m_powerFlag = false;
			m_powerTimer = 0.0f;
			m_powerReleaseTimer = 0.0f;
			m_powerReleaseFlag = false;
		}
	}
	else {
		m_powerFlag = false;
		m_powerTimer = 0.0f;
		m_powerReleaseTimer = 0.0f;
		m_powerReleaseFlag = false;
	}
}