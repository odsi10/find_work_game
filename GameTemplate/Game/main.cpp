#include "stdafx.h"
#include "system/system.h"

//���N���X���C���N���[�h����
#include "Game.h"
#include "Bloom.h"
#include "ModelStandard.h"
#include "ShadowMap.h"

void InitRootSignature(RootSignature& rs);

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	RootSignature rs;
	InitRootSignature(rs);

    ShadowMap shadowMap;

	//�Q�[���̃C���X�^���X���쐬�B
	Game* m_game = NewGO<Game>(0);

	//�u���[���̃C���X�^���X���쐬�B
    //Bloom* m_bloom = NewGO<Bloom>(0);

	//�u���[����������
    //m_bloom->Init();

    //const char* filePath = nullptr;

    //const char* m_tkmFilePath = nullptr; //tkm�t�@�C���̃t�@�C���p�X
    ////tkm�t�@�C���̃t�@�C���p�X��ێ�
    //m_tkmFilePath = filePath;

    //filePath= "Assets/modelData/unityChan.tkm";

    //// �e�`��p�̃��C�g�J�������쐬����
    //Camera lightCamera;

    //// �J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu
    //lightCamera.SetPosition(0, 500, 0);

    //// �J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
    //lightCamera.SetTarget(0, 0, 0);

    //// �������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
    //lightCamera.SetUp(1, 0, 0);

    //// ���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���
    //lightCamera.Update();

    //// step-1 �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
    //float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //RenderTarget shadowMap1;
    //shadowMap1.Create(
    //    1024,
    //    1024,
    //    1,
    //    1,
    //    //�y���ځz�V���h�E�}�b�v�̃J���[�o�b�t�@�̃t�H�[�}�b�g��ύX���Ă���B
    //    DXGI_FORMAT_R32_FLOAT,
    //    DXGI_FORMAT_D32_FLOAT,
    //    clearColor
    //);

    //// step-2 �V���h�E�}�b�v�ɕ`�悷�郂�f��������������
    //ModelInitData teapotShadowModelInitData;
    ////�V���h�E�}�b�v�`��p�̃V�F�[�_�[���w�肷��B
    //teapotShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
    //teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";

    ////�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g�ɕύX���������̂ŁA��������ύX����B
    //teapotShadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

   /* Model teapotShadowModel;
    teapotShadowModel.Init(teapotShadowModelInitData);
    teapotShadowModel.UpdateWorldMatrix(
        { 0, 50, 0 },
        g_quatIdentity,
        g_vec3One
    );*/

    //// �ʏ�`��̃e�B�[�|�b�g���f����������
    //ModelStandard teapotModel;
    //teapotModel.Init("Assets/modelData/teapot.tkm");
    //teapotModel.Update(
    //    { 0, 50, 0 },
    //    g_quatIdentity,
    //    g_vec3Oneu
    //);

    //// �e���󂯂�w�i���f����������
    //ModelInitData bgModelInitData;

    //// �V���h�E���V�[�o�[�i�e�����Ƃ���郂�f���j�p�̃V�F�[�_�[���w�肷��
    //bgModelInitData.m_fxFilePath = "Assets/shader/ShadowReciever.fx";

    ////�V���h�E�}�b�v���g��SRV�ɐݒ肷��
    //bgModelInitData.m_expandShaderResoruceView = &shadowMap.GetRenderTarget().GetRenderTargetTexture();
    //
    //// ���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�[�ɐݒ肷��
    //bgModelInitData.m_expandConstantBuffer = (void*)&shadowMap.GetLightCamera().GetViewProjectionMatrix();
    //bgModelInitData.m_expandConstantBufferSize = sizeof(shadowMap.GetLightCamera().GetViewProjectionMatrix());
    //bgModelInitData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
    //
    //Model bgModel;
    //bgModel.Init(bgModelInitData);
    
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
       /* Quaternion qAddRot;
        qAddRot.SetRotationDegX(g_pad[0]->GetLStickYF());
        g_camera3D->RotateOriginTarget(qAddRot);*/

        GameObjectManager::GetInstance()->ExecuteUpdate(&shadowMap);

		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂B
        //m_bloom->DrowWait(renderContext);
        
        shadowMap.Drow(renderContext);

        GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//�u���[����`��
        //m_bloom->DrowFinish(renderContext);

        //// �V���h�E�}�b�v�Ƀ����_�����O
        //// �����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����
        //renderContext.WaitUntilToPossibleSetRenderTarget(shadowMap);
        //renderContext.SetRenderTargetAndViewport(shadowMap);
        //renderContext.ClearRenderTargetView(shadowMap);

        //// �e���f����`��
        //teapotShadowModel.Draw(renderContext, lightCamera);

        //// �������݊����҂�
        //renderContext.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        //// �ʏ탌���_�����O
        //// �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
        //renderContext.SetRenderTarget(
        //    g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
        //    g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        //);
        //renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

        //// �e�B�[�|�b�g���f����`��
        //teapotModel.Draw(renderContext);

        //// �e���󂯂�w�i��`��
        //bgModel.Draw(renderContext);

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

// ���[�g�V�O�l�`���̏�����
void InitRootSignature(RootSignature& rs)
{
    rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}