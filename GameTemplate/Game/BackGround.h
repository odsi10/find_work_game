#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"
#include "physics/Physics.h"

// 他クラスを使うために宣言する
class ModelRender;
class ShadowMap;

class BackGround : public IGameObject
{
public:	//コンストラクタ諸々
	BackGround();
	~BackGround();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//データメンバ
	ModelRender* m_backGroundModel = nullptr;
	PhysicsStaticObject m_backGroundPSO;

	Vector3 m_position = { 0,0,0 };
};

