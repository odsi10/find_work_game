#pragma once

//他クラスをインクルードする
#include"GaussianBlur.h"

class Bloom : public IGameObject
{
public:	//コンストラクタ諸々
	Bloom();
	~Bloom();
	bool Start() override final;
	void Update() override final;

public:	//メンバ関数
	//初期化処理
	void Init();

	void DrowWait(RenderContext& renderContext);

	void DrowFinish(RenderContext& renderContext);

private:	//データメンバ
	RootSignature rs;
	RenderTarget mainRenderTarget;
	RenderTarget luminnceRenderTarget;
	SpriteInitData luminanceSpriteInitData;
	Sprite luminanceSprite;
	GaussianBlur gaussianBlur[4];
	SpriteInitData finalSpriteInitData;
	Sprite finalSprite;
	SpriteInitData spriteInitData;
	Sprite copyToFrameBufferSprite;
};

