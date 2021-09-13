#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{
}

SkinModelRender::~SkinModelRender()
{
}

bool SkinModelRender::Start()
{
	return true;
}

void SkinModelRender::Init(const char* filePath)
{
	//tkm�t�@�C���̃t�@�C���p�X��ێ�
	m_tkmFilePath = filePath;

	//���f���̏�����
	InitModel(filePath);

	//����������
	m_finishInit = true;
}

void SkinModelRender::InitModel(const char* filePath)
{

	//3D���f�������[�h���邽�߂̏���ݒ肷��
	ModelInitData modelInitData;
	//tkm�t�@�C���̃t�@�C���p�X��ݒ�
	modelInitData.m_tkmFilePath = filePath;
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ�
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	//�����������g���ă��f���\������������������
	m_model.Init(modelInitData);
}

////////////////////////////////////////////////////////////
// �`�揈��
////////////////////////////////////////////////////////////

void SkinModelRender::Render(RenderContext& renderContext)
{
	//����������
	if (m_finishInit == false) {
		return;
	}

	//���f���̕`��
	m_model.Draw(renderContext);
}

void SkinModelRender::Update()
{
	//����������
	if (m_finishInit == false) {
		return;
	}

	//���f���̍��W�X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}