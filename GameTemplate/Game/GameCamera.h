#pragma once

// ���N���X���g�����߂ɐ錾������
class Player;

class GameCamera : public IGameObject
{
public:	//�R���X�g���N�^���X
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

public:
	Player* m_player = nullptr;
	
	Vector3 m_position = { 0.0f,0.0f,0.0f };
	Vector3 m_target = { 0.0f,0.0f,0.0f };
};

