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

	AnimationClip m_playerAnimation[AnimationMax];	//アニメーションクリップ

private:	//データメンバ
	ModelRender* m_enemyModel = nullptr;
	CharacterController m_enemyCC;

	Vector3 m_position = { 00.0f,0.0f,0.0f };
};

