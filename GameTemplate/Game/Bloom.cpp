#include "stdafx.h"
#include "Bloom.h"

Bloom::Bloom()
{
}

Bloom::~Bloom()
{
}

bool Bloom::Start()
{
	return true;
}

void Bloom::Update()
{
}

void Bloom::Init()
{
    // 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
    m_mainRenderTarget.Create(
        1280,
        720,
        1,
        1,
        // 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    // 輝度抽出用のレンダリングターゲットを作成
    // 解像度、ミニマップレベル
    m_luminnceRenderTarget.Create(
        1280,       // 解像度はメインレンダリングターゲットと同じ。
        720,        // 解像度はメインレンダリングターゲットと同じ。
        1,
        1,
        // 【注目】カラーバッファのフォーマットを32bit浮動小数点にしている。
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    // 輝度抽出用のスプライトを初期化
    // 初期化情報を作成する。
    SpriteInitData luminanceSpriteInitData;
    // 輝度抽出用のシェーダーのファイルパスを指定する。
    luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    // 頂点シェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
    // ピクセルシェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
    // スプライトの幅と高さはluminnceRenderTargetと同じ。
    luminanceSpriteInitData.m_width = 1280;
    luminanceSpriteInitData.m_height = 720;
    // テクスチャはメインレンダリングターゲットのカラーバッファ。
    luminanceSpriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
    // 描き込むレンダリングターゲットのフォーマットを指定する。
    luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    // 作成した初期化情報をもとにスプライトを初期化する。
    m_luminanceSprite.Init(luminanceSpriteInitData);

    // ガウシアンブラーを初期化
    // gaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける。
    m_gaussianBlur[0].Init(&m_luminnceRenderTarget.GetRenderTargetTexture());
    // gaussianBlur[1]はgaussianBlur[0]のテクスチャにガウシアンブラーをかける。
    m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
    // gaussianBlur[2]はgaussianBlur[1]のテクスチャにガウシアンブラーをかける。
    m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
    // gaussianBlur[3]はgaussianBlur[2]のテクスチャにガウシアンブラーをかける。
    m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

    // ボケ画像を合成して書き込むためのスプライトを初期化
    // 初期化情報を設定する。
    SpriteInitData finalSpriteInitData;
    // ボケテクスチャを4枚指定する。
    finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
    finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
    finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
    finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
    // 解像度はmainRenderTargetの幅と高さ。
    finalSpriteInitData.m_width = 1280;
    finalSpriteInitData.m_height = 720;
    // ボケ画像を合成する。
    finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
    // ただし、加算合成で描画するので、アルファブレンディングモードを加算にする。
    finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
    // カラーバッファのフォーマットは例によって、32ビット浮動小数点バッファ。
    finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    // 初期化情報を元に加算合成用のスプライトを初期化する。
    
    m_finalSprite.Init(finalSpriteInitData);

    // テクスチャを貼り付けるためのスプライトを初期化する
    // スプライトの初期化オブジェクトを作成する。
    SpriteInitData spriteInitData;
    //テクスチャはmainRenderTargetのカラーバッファ。
    spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
    spriteInitData.m_width = 1280;
    spriteInitData.m_height = 720;
    // モノクロ用のシェーダーを指定する。
    spriteInitData.m_fxFilePath = "Assets/shader/2D.fx";
    // 初期化オブジェクトを使って、スプライトを初期化する。
    Sprite copyToFrameBufferSprite;
    copyToFrameBufferSprite.Init(spriteInitData);
}

void Bloom::DrawWait(RenderContext& renderContext)
{
    // レンダリングターゲットをmainRenderTargetに変更する
    //レンダリングターゲットとして利用できるまで待つ。
    renderContext.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
    // レンダリングターゲットを設定。
    renderContext.SetRenderTargetAndViewport(m_mainRenderTarget);
    // レンダリングターゲットをクリア。
    renderContext.ClearRenderTargetView(m_mainRenderTarget);
    // レンダリングターゲットのへの書き込み終了待ち。
    renderContext.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

}

void Bloom::DrawFinish(RenderContext& renderContext)
{
    // 輝度抽出
    // 輝度抽出用のレンダリングターゲットに変更。
    renderContext.WaitUntilToPossibleSetRenderTarget(m_luminnceRenderTarget);
    // レンダリングターゲットを設定。
    renderContext.SetRenderTargetAndViewport(m_luminnceRenderTarget);
    // レンダリングターゲットをクリア。
    renderContext.ClearRenderTargetView(m_luminnceRenderTarget);
    // 輝度抽出を行う。
    m_luminanceSprite.Draw(renderContext);
    // レンダリングターゲットへの書き込み終了待ち。
    renderContext.WaitUntilFinishDrawingToRenderTarget(m_luminnceRenderTarget);

    // ガウシアンブラーを4回実行する
    m_gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
    m_gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
    m_gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
    m_gaussianBlur[3].ExecuteOnGPU(renderContext, 10);

    // ボケ画像をメインレンダリングターゲットに加算合成
    // レンダリングターゲットとして利用できるまで待つ。
    renderContext.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
    // レンダリングターゲットを設定。
    renderContext.SetRenderTargetAndViewport(m_mainRenderTarget);
    // 最終合成。
    m_finalSprite.Draw(renderContext);
    // レンダリングターゲットへの書き込み終了待ち。
    renderContext.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

    // メインレンダリングターゲットの絵をフレームバッファーにコピー
    renderContext.SetRenderTarget(
        g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        g_graphicsEngine->GetCurrentFrameBuffuerDSV()
    );
    m_copyToFrameBufferSprite.Draw(renderContext);
}