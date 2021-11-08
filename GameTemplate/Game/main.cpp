#include "stdafx.h"
#include "system/system.h"

//他クラスをインクルードする
#include "Game.h"
#include "Bloom.h"
#include "ModelStandard.h"
#include "ShadowMap.h"

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

	//ゲームオブジェクトマネージャーのインスタンスを作成する。
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	RootSignature rs;
	InitRootSignature(rs);

    ShadowMap shadowMap;

	//ゲームのインスタンスを作成。
	Game* m_game = NewGO<Game>(0);

	//ブルームのインスタンスを作成。
    //Bloom* m_bloom = NewGO<Bloom>(0);

	//ブルームを初期化
    //m_bloom->Init();

    //const char* filePath = nullptr;

    //const char* m_tkmFilePath = nullptr; //tkmファイルのファイルパス
    ////tkmファイルのファイルパスを保持
    //m_tkmFilePath = filePath;

    //filePath= "Assets/modelData/unityChan.tkm";

    //// 影描画用のライトカメラを作成する
    //Camera lightCamera;

    //// カメラの位置を設定。これはライトの位置
    //lightCamera.SetPosition(0, 500, 0);

    //// カメラの注視点を設定。これがライトが照らしている場所
    //lightCamera.SetTarget(0, 0, 0);

    //// 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
    //lightCamera.SetUp(1, 0, 0);

    //// ライトビュープロジェクション行列を計算している
    //lightCamera.Update();

    //// step-1 シャドウマップ描画用のレンダリングターゲットを作成する
    //float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //RenderTarget shadowMap1;
    //shadowMap1.Create(
    //    1024,
    //    1024,
    //    1,
    //    1,
    //    //【注目】シャドウマップのカラーバッファのフォーマットを変更している。
    //    DXGI_FORMAT_R32_FLOAT,
    //    DXGI_FORMAT_D32_FLOAT,
    //    clearColor
    //);

    //// step-2 シャドウマップに描画するモデルを初期化する
    //ModelInitData teapotShadowModelInitData;
    ////シャドウマップ描画用のシェーダーを指定する。
    //teapotShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
    //teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";

    ////【注目】カラーバッファのフォーマットに変更が入ったので、こちらも変更する。
    //teapotShadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

   /* Model teapotShadowModel;
    teapotShadowModel.Init(teapotShadowModelInitData);
    teapotShadowModel.UpdateWorldMatrix(
        { 0, 50, 0 },
        g_quatIdentity,
        g_vec3One
    );*/

    //// 通常描画のティーポットモデルを初期化
    //ModelStandard teapotModel;
    //teapotModel.Init("Assets/modelData/teapot.tkm");
    //teapotModel.Update(
    //    { 0, 50, 0 },
    //    g_quatIdentity,
    //    g_vec3Oneu
    //);

    //// 影を受ける背景モデルを初期化
    //ModelInitData bgModelInitData;

    //// シャドウレシーバー（影が落とされるモデル）用のシェーダーを指定する
    //bgModelInitData.m_fxFilePath = "Assets/shader/ShadowReciever.fx";

    ////シャドウマップを拡張SRVに設定する
    //bgModelInitData.m_expandShaderResoruceView = &shadowMap.GetRenderTarget().GetRenderTargetTexture();
    //
    //// ライトビュープロジェクション行列を拡張定数バッファーに設定する
    //bgModelInitData.m_expandConstantBuffer = (void*)&shadowMap.GetLightCamera().GetViewProjectionMatrix();
    //bgModelInitData.m_expandConstantBufferSize = sizeof(shadowMap.GetLightCamera().GetViewProjectionMatrix());
    //bgModelInitData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
    //
    //Model bgModel;
    //bgModel.Init(bgModelInitData);
    
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
       /* Quaternion qAddRot;
        qAddRot.SetRotationDegX(g_pad[0]->GetLStickYF());
        g_camera3D->RotateOriginTarget(qAddRot);*/

        GameObjectManager::GetInstance()->ExecuteUpdate(&shadowMap);

		//レンダリングターゲットとして利用できるまで待つ。
        //m_bloom->DrowWait(renderContext);
        
        shadowMap.Drow(renderContext);

        GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//ブルームを描画
        //m_bloom->DrowFinish(renderContext);

        //// シャドウマップにレンダリング
        //// レンダリングターゲットをシャドウマップに変更する
        //renderContext.WaitUntilToPossibleSetRenderTarget(shadowMap);
        //renderContext.SetRenderTargetAndViewport(shadowMap);
        //renderContext.ClearRenderTargetView(shadowMap);

        //// 影モデルを描画
        //teapotShadowModel.Draw(renderContext, lightCamera);

        //// 書き込み完了待ち
        //renderContext.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        //// 通常レンダリング
        //// レンダリングターゲットをフレームバッファに戻す
        //renderContext.SetRenderTarget(
        //    g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        //    g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        //);
        //renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

        //// ティーポットモデルを描画
        //teapotModel.Draw(renderContext);

        //// 影を受ける背景を描画
        //bgModel.Draw(renderContext);

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