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

void SkinModelRender::Init(const char* filePath,
	enModelUpAxis::EnModelUpAxis modelUpAxis
)
{
	//tkm�t�@�C���̃t�@�C���p�X��ێ�
	m_tkmFilePath = filePath;

	//���f���̏�����
	InitModel(filePath);

	//����������
	m_finishInit = true;
}

void SkinModelRender::InitModel(const char* filePath,
	enModelUpAxis::EnModelUpAxis modelUpAxis
)
{
	//���C�g�̐ݒ�
	//�f�B���N�V�������C�g������������B
	InitDirectionLight();
	//3D���f�������[�h���邽�߂̏���ݒ肷��
	ModelInitData modelInitData;
	
	//tkm�t�@�C���̃t�@�C���p�X��ݒ�
	modelInitData.m_tkmFilePath = filePath;
	
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ�
	modelInitData.m_fxFilePath = "Assets/shader/model.fx";

	//���C�g�̏���萔�o�b�t�@�Ƃ��ăf�B�X�N���v�^�q�[�v��
	//�o�^���邽�߂Ƀ��f���̏��������Ƃ��ēn���B
	modelInitData.m_expandConstantBuffer = &m_light;
	modelInitData.m_expandConstantBufferSize = sizeof(m_light);

	//�����������g���ă��f���\������������������
	m_model.Init(modelInitData);
}

//////////////////////////////
// ���C�g���Ƃ̏�����
//////////////////////////////

void SkinModelRender::InitDirectionLight()
{
	//���C�g�͎΂ߏォ�瓖�����Ă���B
	m_light.ligDirection.x = 1.0f;
	m_light.ligDirection.y = -1.0f;
	m_light.ligDirection.z = -1.0f;
	//���K������B
	m_light.ligDirection.Normalize();
	//���C�g�̃J���[�̐ݒ�i���C�g�̋����j
	m_light.ligColor.x = 1.5f;
	m_light.ligColor.y = 1.5f;
	m_light.ligColor.z = 1.5f;

	//���_�̈ʒu��ݒ�
	m_light.eyePos = g_camera3D->GetPosition();
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