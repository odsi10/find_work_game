#pragma once

// 他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "Player.h"

// 他クラスを使うために宣言する
class ModelRender;
class Player;

class Enemy : public IGameObject
{
public:	// コンストラクタ諸々
	Enemy();
	~Enemy();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public: // Set関数
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

public: // Get関数
	const Vector3& GetPosition()
	{
		return m_position;
	}

private:	//アニメーション
	enum AnimationEnum	//アニメーションのenum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	// アニメーションクリップ

private:	//データメンバ
	ModelRender* m_enemyModel = nullptr;			// モデルレンダラー
	Player* m_player = nullptr;

	Vector3 m_position = { 0.0f,0.0f,0.0f };		// モデルの位置
	
};