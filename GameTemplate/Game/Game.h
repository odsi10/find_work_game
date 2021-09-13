#pragma once

//他クラスをインクルードする
#include"SkinModelRender.h"
#include"Name.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start() override final;
	void Update() override final;

private:
	SkinModelRender* m_playerModel = nullptr;
};

