#pragma once

// 他クラスを使うために宣言をする
class Player;

class GameCamera : public IGameObject
{
public:	//コンストラクタ諸々
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

public:
	Player* m_player = nullptr;
	
	Vector3 m_position = { 0.0f,0.0f,0.0f };
	Vector3 m_target = { 0.0f,0.0f,0.0f };
};

