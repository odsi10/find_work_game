#pragma once

// 他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"
#include "ShadowMap.h"
#include "ModelRender.h"

// 他クラスを使うために宣言する
class ShadowMap;
class ModelRender;

class Player : public IGameObject
{
public:	// コンストラクタ諸々
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public:	// Get関数
	const Vector3 GetPosition()
	{
		return m_position;
	}

private:	// アニメーション
	enum AnimationEnum	// アニメーションのenum
	{
		Idle,
		MoveForward,
		MoveForwardSecondPower,
		MoveForwardThirdPower,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//アニメーションクリップ

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

private:	// データメンバ
	ModelRender* m_playerModel = nullptr;	// モデルレンダラー
	CharacterController m_playerCC;			// キャラクターコントローラー

	Vector3 m_position = { 0.0f,0.0f,500.0f };		 // プレイヤーの位置
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };		 // 移動量
	float m_fSpeed = -6.0f;							 // 基礎移動量
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f }; // 回転
	float m_angle;									 // 回転	
	Quaternion m_qRot;								 // 回転

	float m_powerTimer = 0.0f;	// パワーをためている時間をはかるタイマー
	bool m_powerFlag = false;
	float m_powerReleaseTimer = 0.0f;
	bool m_powerReleaseFlag = false;
};