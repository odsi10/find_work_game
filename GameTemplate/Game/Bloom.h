#pragma once

//他クラスをインクルードする
#include"GaussianBlur.h"

class Bloom : public IGameObject
{
public:	//コンストラクタ諸々
	Bloom();
	~Bloom();
	bool Start() ;
	void Update();

public:	//メンバ関数
	//初期化処理
	void Init();

	void DrowWait(RenderContext& renderContext);

	void DrowFinish(RenderContext& renderContext);

private:	//データメンバ
	RenderTarget mainRenderTarget;	// 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
	RenderTarget luminnceRenderTarget;	// 輝度抽出用のレンダリングターゲットを作成
	SpriteInitData luminanceSpriteInitData;
	Sprite luminanceSprite;
	GaussianBlur gaussianBlur[4];
	SpriteInitData finalSpriteInitData;
	Sprite finalSprite;
	SpriteInitData spriteInitData;
	Sprite copyToFrameBufferSprite;
};

