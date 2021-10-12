#pragma once

//他クラスをインクルードする
#include "ModelRender.h"
#include "Name.h"

class BackGround : public IGameObject
{
public:	//コンストラクタ諸々
	BackGround();
	~BackGround();
	bool Start() override final;
	void Update() override final;

private:	//データメンバ
	ModelRender* m_backGroundModel = nullptr;
};

