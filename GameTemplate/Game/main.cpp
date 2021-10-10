#include "stdafx.h"
#include "system/system.h"

//他クラスをインクルードする
#include"Game.h"
#include"Bloom.h"

const int NUM_WEIGHTS = 8;

/// <summary>
/// ブラー用のパラメータ
/// </summary>
struct SBlurParam
{
    float weights[NUM_WEIGHTS];
};

void InitRootSignature(RootSignature& rs);

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////
	g_camera3D->SetPosition({ 0.0f, 50.0f, 150.0f });

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	Game* m_game = NewGO<Game>(0);

    Bloom* m_bloom = NewGO<Bloom>(0);

    RootSignature rs;
    InitRootSignature(rs);

    // 32ビットの浮動小数点のカラーバッファーを保持したメインレンダリングターゲットを作成する
    RenderTarget mainRenderTarget;
    mainRenderTarget.Create(
        1280,
        720,
        1,
        1,
        // 【注目】カラーバッファーのフォーマットを32bit浮動小数点にしている
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    //輝度抽出用のレンダリングターゲットを作成
    RenderTarget luminnceRenderTarget;
    //解像度、ミニマップレベル
    luminnceRenderTarget.Create(
        1280,       //解像度はメインレンダリングターゲットと同じ。
        720,        //解像度はメインレンダリングターゲットと同じ。
        1,
        1,
        //【注目】カラーバッファのフォーマットを32bit浮動小数点にしている。
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    //輝度抽出用のスプライトを初期化
    //初期化情報を作成する。
    SpriteInitData luminanceSpriteInitData;
    //輝度抽出用のシェーダーのファイルパスを指定する。
    luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    //頂点シェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
    //ピクセルシェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
    //スプライトの幅と高さはluminnceRenderTargetと同じ。
    luminanceSpriteInitData.m_width = 1280;
    luminanceSpriteInitData.m_height = 720;
    //テクスチャはメインレンダリングターゲットのカラーバッファ。
    luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    //描き込むレンダリングターゲットのフォーマットを指定する。
    luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //作成した初期化情報をもとにスプライトを初期化する。
    Sprite luminanceSprite;
    luminanceSprite.Init(luminanceSpriteInitData);
    //ガウシアンブラーを初期化
    GaussianBlur gaussianBlur[4];
    //gaussianBlur[0]は輝度テクスチャにガウシアンブラーをかける。
    gaussianBlur[0].Init(&luminnceRenderTarget.GetRenderTargetTexture());
    //gaussianBlur[1]はgaussianBlur[0]のテクスチャにガウシアンブラーをかける。
    gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
    //gaussianBlur[2]はgaussianBlur[1]のテクスチャにガウシアンブラーをかける。
    gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
    //gaussianBlur[3]はgaussianBlur[2]のテクスチャにガウシアンブラーをかける。
    gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());

    //ボケ画像を合成して書き込むためのスプライトを初期化
    //初期化情報を設定する。
    SpriteInitData finalSpriteInitData;
    //ボケテクスチャを4枚指定する。
    finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
    finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
    finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
    finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
    //解像度はmainRenderTargetの幅と高さ。
    finalSpriteInitData.m_width = 1280;
    finalSpriteInitData.m_height = 720;
    //ボケ画像を合成する。
    finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
    //ただし、加算合成で描画するので、アルファブレンディングモードを加算にする。
    finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
    //カラーバッファのフォーマットは例によって、32ビット浮動小数点バッファ。
    finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //初期化情報を元に加算合成用のスプライトを初期化する。
    Sprite finalSprite;
    finalSprite.Init(finalSpriteInitData);

    //テクスチャを貼り付けるためのスプライトを初期化する
    //スプライトの初期化オブジェクトを作成する。
    SpriteInitData spriteInitData;
    //テクスチャはmainRenderTargetのカラーバッファ。
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    spriteInitData.m_width = 1280;
    spriteInitData.m_height = 720;
    //モノクロ用のシェーダーを指定する。
    spriteInitData.m_fxFilePath = "Assets/shader/2D.fx";
    //初期化オブジェクトを使って、スプライトを初期化する。
    Sprite copyToFrameBufferSprite;
    copyToFrameBufferSprite.Init(spriteInitData);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		GameObjectManager::GetInstance()->ExecuteUpdate();
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

        //レンダリングターゲットをmainRenderTargetに変更する
        //レンダリングターゲットとして利用できるまで待つ。
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //レンダリングターゲットをクリア。
        renderContext.ClearRenderTargetView(mainRenderTarget);
        
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);
        
        //レンダリングターゲットのへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

        //輝度抽出
        //輝度抽出用のレンダリングターゲットに変更。
        renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);
        //レンダリングターゲットをクリア。
        renderContext.ClearRenderTargetView(luminnceRenderTarget);
        //輝度抽出を行う。
        luminanceSprite.Draw(renderContext);
        //レンダリングターゲットへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);

        //ガウシアンブラーを4回実行する
        gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[3].ExecuteOnGPU(renderContext, 10);

        //ボケ画像をメインレンダリングターゲットに加算合成
        //レンダリングターゲットとして利用できるまで待つ。
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //最終合成。
        finalSprite.Draw(renderContext);
        //レンダリングターゲットへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

        //メインレンダリングターゲットの絵をフレームバッファーにコピー
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        copyToFrameBufferSprite.Draw(renderContext);

		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

// ルートシグネチャの初期化
void InitRootSignature(RootSignature& rs)
{
    rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}