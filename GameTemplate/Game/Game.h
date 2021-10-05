#pragma once

//���N���X���C���N���[�h����
#include"SkinModelRender.h"
#include"Name.h"

class SkinModelRender;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start() override final;
	void Update() override final;

private:
	SkinModelRender* m_playerModel = nullptr;
	SkinModelRender* m_backGround = nullptr;
};

