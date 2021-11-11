#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    ShadowRenderTarget();
}

ShadowMap::~ShadowMap()
{
}

bool ShadowMap::Start()
{
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

void ShadowMap::Draw(RenderContext& renderContext)
{
    // カメラの位置を設定。これはライトの位置
    m_lightCamera.SetPosition(1000, 1000, 1000);

    // カメラの注視点を設定。これがライトが照らしている場所
    m_lightCamera.SetTarget(0, 0, 0);

    // 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
    m_lightCamera.SetUp(1, 0, 0);

    m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
    m_lightCamera.SetWidth(500.0f);
    m_lightCamera.SetHeight(500.0f);
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

    // 通常レンダリング
    // レンダリングターゲットをフレームバッファに戻す
    renderContext.SetRenderTarget(
        g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        g_graphicsEngine->GetCurrentFrameBuffuerDSV()
    );
    renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
}