#include "stdafx.h"
#include "system/system.h"

//���N���X���C���N���[�h����
#include"Game.h"
#include"Bloom.h"

//void InitRootSignature(RootSignature& rs);

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
	g_camera3D->SetPosition({ 0.0f, 50.0f, 150.0f });

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();

	//�Q�[���̃C���X�^���X���쐬�B
	Game* m_game = NewGO<Game>(0);

	//�u���[���̃C���X�^���X���쐬�B
    Bloom* m_bloom = NewGO<Bloom>(0);

    /*RootSignature rs;
    InitRootSignature(rs);*/

	//�u���[����������
    m_bloom->Init();

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

		GameObjectManager::GetInstance()->ExecuteUpdate();

		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂B
        m_bloom->DrowWait(renderContext);
        
        GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//�u���[����`��
        m_bloom->DrowFinish(renderContext);
        
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

//// ���[�g�V�O�l�`���̏�����
//void InitRootSignature(RootSignature& rs)
//{
//    rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP,
//        D3D12_TEXTURE_ADDRESS_MODE_WRAP);
//}