#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"
#include "ShadowMap.h"
#include "ModelRender.h"

class ShadowMap;
class ModelRender;

class Player : public IGameObject
{
public:	//コンストラクタ諸々
	Player();
	~Player();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public:	//Get関数
	const Vector3 GetPosition()
	{
		return m_position;
	}
	
private:	//アニメーション
	enum AnimationEnum	//アニメーションのenum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//アニメーションクリップ

private:	// 移動処理
	void Move();
	void Rotation();

private:	//データメンバ
	ModelRender* m_playerModel = nullptr;

	CharacterController m_playerCC;
	Vector3 m_position = { 0.0f,0.0f,0.0f };
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	float fSpeed = -6.0f;
	Quaternion m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	float angle;
	Quaternion qRot;
};

