#pragma once

//他クラスをインクルードする
#include "SkinModelRender.h"
#include "Name.h"

//他クラスを使うために宣言をする
class SkinModelRender;
class Player;
class BackGround;

class Game : public IGameObject
{
public:	//コンストラクタ諸々
	Game();
	~Game();
	bool Start() override final;
	void Update() override final;

private:	//データメンバ
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
};

