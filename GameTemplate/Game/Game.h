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
class PlayerEnemyHit;

class Game : public IGameObject
{
public:	// �R���X�g���N�^���X
	Game();
	~Game();
	bool Start(ShadowMap* shadowMap);
	void Update();

private:	// �f�[�^�����o
	BackGround* m_backGround = nullptr;			// �X�e�[�W
	Player* m_player = nullptr;					// �v���C���[
	GameCamera* m_gameCamera = nullptr;			// �Q�[���J����
	Enemy* m_enemy = nullptr;					// �G�l�~�[
	PlayerEnemyHit* m_playerEnemyHit = nullptr; // �v���C���[�ƓG�����������Ƃ��̐�����΂�����
};

