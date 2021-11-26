#pragma once

// 他クラスを使うために宣言をする
class Player;

class GameCamera : public IGameObject
{
public:	//コンストラクタ諸々
	GameCamera();
	~GameCamera();
	bool Start(ShadowMap* shadowMap);
	void Update();

public:
	Player* m_player = nullptr;	// プレイヤー
	
	Vector3 m_position = { 0.0f,0.0f,0.0f };	// 位置
	Vector3 m_target = { 0.0f,0.0f,0.0f };		// カメラのターゲット
};

