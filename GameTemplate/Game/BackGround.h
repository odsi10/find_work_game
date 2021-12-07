#pragma once

//他クラスをインクルードする
#include <Model.h>

#include "ModelRender.h"
#include "Name.h"
//#include "physics/Physics.h"

// 他クラスを使うために宣言する
class Model;

class BackGround : public IGameObject
{
public:	//コンストラクタ諸々
	BackGround();
	~BackGround();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();

private:	//データメンバ
	ModelRender* m_backGroundModel = nullptr;	// モデルレンダラー
	//PhysicsStaticObject m_backGroundPSO;		// 静的オブジェクトのコリジョン	
	
	Vector3 m_position = { 0,0,0 };				// オブジェクトの位置
};