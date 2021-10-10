#pragma once

//���N���X���C���N���[�h����
#include "SkinModelRender.h"
#include "Name.h"
#include "Bloom.h"

//���N���X���g�����߂ɐ錾������
class SkinModelRender;
class BackGround;
class Player;

class Game : public IGameObject
{
public:	//�R���X�g���N�^���X
	Game();
	~Game();
	bool Start() override final;
	void Update() override final;

private:	//�f�[�^�����o
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
};

