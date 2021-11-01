#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"

// 他クラスを使うために宣言をする
class BackGround;
class Player;
class GameCamera;
class Enemy;
class ShadowMap;

class Game : public IGameObject
{
public:	// コンストラクタ諸々
	Game();
	~Game();
	bool Start(ShadowMap& shadowMap) override final;
	void Update();

private:	// データメンバ
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy = nullptr;
};

