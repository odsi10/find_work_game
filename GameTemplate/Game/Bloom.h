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
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// レンダリングターゲット利用
	/// </summary>
	/// <param name="renderContext"></param>
	void DrawWait(RenderContext& renderContext);

	void DrawFinish(RenderContext& renderContext);

private:	//データメンバ
	RenderTarget m_mainRenderTarget;	// 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
	RenderTarget m_luminnceRenderTarget;	// 輝度抽出用のレンダリングターゲットを作成
	Sprite m_luminanceSprite;
	GaussianBlur m_gaussianBlur[4];
	Sprite m_finalSprite;
	Sprite m_copyToFrameBufferSprite;
};

