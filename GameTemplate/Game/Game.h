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
class PlayerEnemyHit;

class Game : public IGameObject
{
public:	// コンストラクタ諸々
	Game();
	~Game();
	bool Start(ShadowMap* shadowMap);
	void Update();

private:	// データメンバ
	BackGround* m_backGround = nullptr;			// ステージ
	Player* m_player = nullptr;					// プレイヤー
	GameCamera* m_gameCamera = nullptr;			// ゲームカメラ
	Enemy* m_enemy = nullptr;					// エネミー
	PlayerEnemyHit* m_playerEnemyHit = nullptr; // プレイヤーと敵が当たったときの吹っ飛ばし処理
};

