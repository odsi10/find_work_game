#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"

class Player : public IGameObject
{
public:	//コンストラクタ諸々
	Player();
	~Player();
	bool Start() override final;
	void Update() override final;

private:	//アニメーション
	enum AnimationEnum	//アニメーションのenum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	//アニメーションクリップ

private:
	ModelRender* m_playerModel = nullptr;
};

