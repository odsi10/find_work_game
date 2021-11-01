#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
}

ShadowMap::~ShadowMap()
{
}

bool ShadowMap::Start()
{
    ShadowRenderTarget();
    return true;
}

void ShadowMap::Update()
{	
}

void ShadowMap::Init()
{
    
}

void ShadowMap::ShadowRenderTarget()
{
    // step-1 シャドウマップ描画用のレンダリングターゲットを作成する
    float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_shadowMap.Create(
        1024,
        1024,
        1,
        1,
        //【注目】シャドウマップのカラーバッファのフォーマットを変更している。
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        clearColor
    );
}

void ShadowMap::Drow(RenderContext& renderContext)
{
    // 影描画用のライトカメラを作成する
    Camera m_lightCamera;

    // カメラの位置を設定。これはライトの位置
    m_lightCamera.SetPosition(0, 500, 0);

    // カメラの注視点を設定。これがライトが照らしている場所
    m_lightCamera.SetTarget(0, 0, 0);

    // 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
    m_lightCamera.SetUp(1, 0, 0);

    // ライトビュープロジェクション行列を計算している
    m_lightCamera.Update();
    // シャドウマップにレンダリング
    // レンダリングターゲットをシャドウマップに変更する
    renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
    renderContext.SetRenderTargetAndViewport(m_shadowMap);
    renderContext.ClearRenderTargetView(m_shadowMap);

    // 影モデルを描画
    for (auto model : m_modelArray) {
        model->Draw(renderContext, m_lightCamera);
    }
    
    // 書き込み完了待ち
    renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);
}