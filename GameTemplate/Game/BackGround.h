#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "physics/Physics.h"

// 他クラスを使うために宣言する
class ModelRender;

class BackGround : public IGameObject
{
public:	//コンストラクタ諸々
	BackGround();
	~BackGround();
	bool Start() override final;
	void Update() override final;

private:	//データメンバ
	ModelRender* m_backGroundModel = nullptr;
	PhysicsStaticObject m_backGroundPSO;

	Vector3 m_position = { 0,0,0 };
};

