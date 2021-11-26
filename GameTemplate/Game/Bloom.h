#pragma once

// 他クラスをインクルードする
#include"GaussianBlur.h"

class Bloom
{
public:	// コンストラクタ諸々
	Bloom();
	~Bloom();
	bool Start() ;
	void Update();

public:	// メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// レンダリングターゲット利用
	/// </summary>
	/// <param name="renderContext"></param>
	void DrawWait(RenderContext& renderContext);

	/// <summary>
	/// 最終工程
	/// </summary>
	/// <param name="renderContext"></param>
	void DrawFinish(RenderContext& renderContext);

private:	//データメンバ
	RenderTarget m_mainRenderTarget;		// 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
	RenderTarget m_luminnceRenderTarget;	// 輝度抽出用のレンダリングターゲットを作成
	Sprite m_luminanceSprite;				// 作成した初期化情報をもとにスプライトを初期化する。
	GaussianBlur m_gaussianBlur[4];			// ガウシアンブラーを初期化
	Sprite m_finalSprite;					// 初期化情報を元に加算合成用のスプライトを初期化する。
	Sprite m_copyToFrameBufferSprite;		// メインレンダリングターゲットの絵をフレームバッファーにコピー
};

