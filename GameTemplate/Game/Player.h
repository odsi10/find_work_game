#pragma once

// 他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "ShadowMap.h"
#include "ModelRender.h"
#include "PlayerEnemyHit.h"

// 他クラスを使うために宣言する
class ShadowMap;
class ModelRender;
class PlayerEnemyHit;

class Player : public IGameObject
{
public:	// コンストラクタ諸々
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

private:	// 移動処理
	/// <summary>
	/// 位置の移動
	/// </summary>
	void Move();

	/// <summary>
	/// プレイヤーの向き
	/// </summary>
	void Rotation();

	/// <summary>
	/// アニメーション
	/// </summary>
	void Animation();

	/// <summary>
	/// パワー放出制御
	/// </summary>
	void PowerRelease();

public:	// Set関数
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	void SetMove(const Vector3 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	void SetPower(const int power)
	{
		m_power = power;
	}

	void SetReleaseTimer(const float releaseTimer)
	{
		m_powerReleaseTimer = releaseTimer;
	}

public:	// Get関数
	const Vector3& GetPosition()
	{
		return m_position;
	}

	const Vector3& GetMove()
	{
		return m_moveSpeed;
	}

	const int& GetPower()
	{
		return m_power;
	}

private:	// アニメーション
	enum AnimationEnum	// アニメーションのenum
	{
		Idle,
		MoveForward,
		MoveForwardSecondPower,
		MoveForwardThirdPower,
		KnockBack,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//アニメーションクリップ

private:	// データメンバ
	ModelRender* m_playerModel = nullptr;	// モデルレンダラー
	PlayerEnemyHit* m_playerEnemyHit = nullptr;

	Vector3 m_position = { 0.0f,0.0f,1000.0f };		 // プレイヤーの位置
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };		 // 移動量
	float m_fSpeed = -6.0f;							 // 基礎移動量
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f }; // 回転
	float m_angle;									 // 回転	
	Quaternion m_qRot;								 // 回転

	float m_powerTimer = 0.0f;	// パワーをためている時間をはかるタイマー
	bool m_powerFlag = false;
	float m_powerReleaseTimer = 0.0f;
	bool m_powerReleaseFlag = false;
	int m_power = 0;
};