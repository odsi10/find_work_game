#include "stdafx.h"
#include "system/system.h"

//他クラスをインクルードする
#include"Game.h"
#include"Bloom.h"

//void InitRootSignature(RootSignature& rs);

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

	//ゲームのインスタンスを作成。
	Game* m_game = NewGO<Game>(0);

	//ブルームのインスタンスを作成。
    Bloom* m_bloom = NewGO<Bloom>(0);

    /*RootSignature rs;
    InitRootSignature(rs);*/

	//ブルームを初期化
    m_bloom->Init();

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

		//レンダリングターゲットとして利用できるまで待つ。
        m_bloom->DrowWait(renderContext);
        
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//ブルームを描画
        m_bloom->DrowFinish(renderContext);
        
		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//ゲームオブジェクトマネージャーを削除。
	GameObjectManager::DeleteInstance();
	return 0;
}

//// ルートシグネチャの初期化
//void InitRootSignature(RootSignature& rs)
//{
//    rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
//}