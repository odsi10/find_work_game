#pragma once

//���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"

// ���N���X���g�����߂ɐ錾������
class BackGround;
class Player;
class GameCamera;
class Enemy;
class ShadowMap;

class Game : public IGameObject
{
public:	// �R���X�g���N�^���X
	Game();
	~Game();
	bool Start(ShadowMap& shadowMap) override final;
	void Update();

private:	// �f�[�^�����o
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy = nullptr;
};

