#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"

// 他クラスを使うために宣言をする
class BackGround;
class Player;
class GameCamera;
class Enemy;

class Game : public IGameObject
{
public:	// コンストラクタ諸々
	Game();
	~Game();
	bool Start() override final;
	void Update() override final;

private:	// データメンバ
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy = nullptr;
};

