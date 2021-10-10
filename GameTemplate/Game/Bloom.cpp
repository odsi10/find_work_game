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
    // 32�r�b�g�̕��������_�̃J���[�o�b�t�@�[��ێ��������C�������_�����O�^�[�Q�b�g���쐬����
    
    mainRenderTarget.Create(
        1280,
        720,
        1,
        1,
        // �y���ځz�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    //�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
   
    //�𑜓x�A�~�j�}�b�v���x��
    luminnceRenderTarget.Create(
        1280,       //�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
        720,        //�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
        1,
        1,
        //�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );

    //�P�x���o�p�̃X�v���C�g��������
    //�����������쐬����B
    
    //�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
    luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    //���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
    luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
    //�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
    luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
    //�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ����B
    luminanceSpriteInitData.m_width = 1280;
    luminanceSpriteInitData.m_height = 720;
    //�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�B
    luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    //�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
    luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //�쐬�����������������ƂɃX�v���C�g������������B
    
    luminanceSprite.Init(luminanceSpriteInitData);
    //�K�E�V�A���u���[��������
    
    //gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������B
    gaussianBlur[0].Init(&luminnceRenderTarget.GetRenderTargetTexture());
    //gaussianBlur[1]��gaussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
    gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
    //gaussianBlur[2]��gaussianBlur[1]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
    gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
    //gaussianBlur[3]��gaussianBlur[2]�̃e�N�X�`���ɃK�E�V�A���u���[��������B
    gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());

    //�{�P�摜���������ď������ނ��߂̃X�v���C�g��������
    //����������ݒ肷��B
    
    //�{�P�e�N�X�`����4���w�肷��B
    finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
    finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
    finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
    finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
    //�𑜓x��mainRenderTarget�̕��ƍ����B
    finalSpriteInitData.m_width = 1280;
    finalSpriteInitData.m_height = 720;
    //�{�P�摜����������B
    finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
    finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
    //�������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���B
    finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
    //�J���[�o�b�t�@�̃t�H�[�}�b�g�͗�ɂ���āA32�r�b�g���������_�o�b�t�@�B
    finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //�������������ɉ��Z�����p�̃X�v���C�g������������B
    
    finalSprite.Init(finalSpriteInitData);

    //�e�N�X�`����\��t���邽�߂̃X�v���C�g������������
    //�X�v���C�g�̏������I�u�W�F�N�g���쐬����B
    
    //�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�B
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    spriteInitData.m_width = 1280;
    spriteInitData.m_height = 720;
    //���m�N���p�̃V�F�[�_�[���w�肷��B
    spriteInitData.m_fxFilePath = "Assets/shader/2D.fx";
    //�������I�u�W�F�N�g���g���āA�X�v���C�g������������B
    
    copyToFrameBufferSprite.Init(spriteInitData);


    
}

void Bloom::DrowWait(RenderContext& renderContext)
{
    //�����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
    //�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂B
    renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
    //�����_�����O�^�[�Q�b�g��ݒ�B
    renderContext.SetRenderTargetAndViewport(mainRenderTarget);
    //�����_�����O�^�[�Q�b�g���N���A�B
    renderContext.ClearRenderTargetView(mainRenderTarget);
    //�����_�����O�^�[�Q�b�g�̂ւ̏������ݏI���҂��B
    renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

}

void Bloom::DrowFinish(RenderContext& renderContext)
{
    //�P�x���o
    //�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX�B
    renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);
    //�����_�����O�^�[�Q�b�g��ݒ�B
    renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);
    //�����_�����O�^�[�Q�b�g���N���A�B
    renderContext.ClearRenderTargetView(luminnceRenderTarget);
    //�P�x���o���s���B
    luminanceSprite.Draw(renderContext);
    //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
    renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);

    //�K�E�V�A���u���[��4����s����
    gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
    gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
    gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
    gaussianBlur[3].ExecuteOnGPU(renderContext, 10);

    //�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
    //�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂B
    renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
    //�����_�����O�^�[�Q�b�g��ݒ�B
    renderContext.SetRenderTargetAndViewport(mainRenderTarget);
    //�ŏI�����B
    finalSprite.Draw(renderContext);
    //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
    renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

    //���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
    renderContext.SetRenderTarget(
        g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        g_graphicsEngine->GetCurrentFrameBuffuerDSV()
    );
    copyToFrameBufferSprite.Draw(renderContext);
}