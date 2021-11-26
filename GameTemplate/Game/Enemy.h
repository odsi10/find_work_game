#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "physics/CharacterController.h"

//他クラスを使うために宣言する
class ModelRender;

class Enemy : public IGameObject
{
public:	//コンストラクタ諸々
	Enemy();
	~Enemy();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//アニメーション
	enum AnimationEnum	//アニメーションのenum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	// アニメーションクリップ

private:	//データメンバ
	ModelRender* m_enemyModel = nullptr;			// モデルレンダラー
	CharacterController m_enemyCC;					// キャラクターコントローラー

	Vector3 m_position = { 0.0f,0.0f,0.0f };		// モデルの位置
};