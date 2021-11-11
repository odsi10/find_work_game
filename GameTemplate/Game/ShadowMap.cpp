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
    // step-1 �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
    float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_shadowMap.Create(
        1024,
        1024,
        1,
        1,
        //�y���ځz�V���h�E�}�b�v�̃J���[�o�b�t�@�̃t�H�[�}�b�g��ύX���Ă���B
        DXGI_FORMAT_R32_FLOAT,
        DXGI_FORMAT_D32_FLOAT,
        clearColor
    );
}

void ShadowMap::Draw(RenderContext& renderContext)
{
    // �J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu
    m_lightCamera.SetPosition(1000, 1000, 1000);

    // �J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
    m_lightCamera.SetTarget(0, 0, 0);

    // �������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
    m_lightCamera.SetUp(1, 0, 0);

    m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
    m_lightCamera.SetWidth(500.0f);
    m_lightCamera.SetHeight(500.0f);
    // ���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���
    m_lightCamera.Update();

    // �V���h�E�}�b�v�Ƀ����_�����O
    // �����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����
    renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
    renderContext.SetRenderTargetAndViewport(m_shadowMap);
    renderContext.ClearRenderTargetView(m_shadowMap);

    // �e���f����`��
    for (auto model : m_modelArray) {
        model->Draw(renderContext, m_lightCamera);
    }
    
    // �������݊����҂�
    renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

    // �ʏ탌���_�����O
    // �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
    renderContext.SetRenderTarget(
        g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        g_graphicsEngine->GetCurrentFrameBuffuerDSV()
    );
    renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
}