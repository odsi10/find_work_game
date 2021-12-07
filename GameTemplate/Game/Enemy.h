#pragma once

// ���N���X���C���N���[�h����
#include "ModelRender.h"
#include "Name.h"
#include "Player.h"

// ���N���X���g�����߂ɐ錾����
class ModelRender;
class Player;

class Enemy : public IGameObject
{
public:	// �R���X�g���N�^���X
	Enemy();
	~Enemy();
	bool Start(ShadowMap* shadowMap) override final;
	void Update() override final;

public: // Set�֐�
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

public: // Get�֐�
	const Vector3& GetPosition()
	{
		return m_position;
	}

private:	//�A�j���[�V����
	enum AnimationEnum	//�A�j���[�V������enum
	{
		moveForward,
		AnimationMax
	};

	AnimationClip m_playerAnimation[AnimationMax];	// �A�j���[�V�����N���b�v

private:	//�f�[�^�����o
	ModelRender* m_enemyModel = nullptr;			// ���f�������_���[
	Player* m_player = nullptr;

	Vector3 m_position = { 0.0f,0.0f,0.0f };		// ���f���̈ʒu
	
};