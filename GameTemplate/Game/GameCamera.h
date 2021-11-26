#pragma once

// ���N���X���g�����߂ɐ錾������
class Player;

class GameCamera : public IGameObject
{
public:	//�R���X�g���N�^���X
	GameCamera();
	~GameCamera();
	bool Start(ShadowMap* shadowMap);
	void Update();

public:
	Player* m_player = nullptr;	// �v���C���[
	
	Vector3 m_position = { 0.0f,0.0f,0.0f };	// �ʒu
	Vector3 m_target = { 0.0f,0.0f,0.0f };		// �J�����̃^�[�Q�b�g
};

