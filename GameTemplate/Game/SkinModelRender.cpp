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
	//���C�g�̐ݒ������B
	//�f�B���N�V�������C�g������������
	InitDirectionLight();

	//�|�C���g���C�g������������
	//InitPointLight();

	//�X�|�b�g���C�g������������
	//InitSpotLight();

	//����������������
	//InitAmbientLight();

	//�������C�g������������
	//InitHemiLight();

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


void SkinModelRender::InitPointLight()
{
	//�|�C���g���C�g�̏������W��ݒ肷��
	m_light.ptPosition.x = 0.0f;
	m_light.ptPosition.y = 50.0f;
	m_light.ptPosition.z = 50.0f;

	//�|�C���g���C�g�̏����J���[��ݒ肷��
	m_light.ptColor.x = 15.0f;
	m_light.ptColor.y = 0.0f;
	m_light.ptColor.z = 240.0f;

	//�|�C���g���C�g�̉e���͈͂�ݒ肷��
	m_light.ptRange = 100.0f;
}

void SkinModelRender::InitSpotLight()
{
	//�������W
	m_light.spPosition.x = 0.0f;
	m_light.spPosition.y = 50.0f;
	m_light.spPosition.z = -150.0f;

	//���C�g�̃J���[
	m_light.spColor.x = 200.0f;
	m_light.spColor.y = 10.0f;
	m_light.spColor.z = 10.0f;
	//���������͎΂߉��ɂ���B
	m_light.spDirection.x = 1.0f;
	m_light.spDirection.y = -1.0f;
	m_light.spDirection.z = 1.0f;
	//���K��
	m_light.spDirection.Normalize();
	//�ˏo�͈͂�300
	m_light.spRange = 300.0f;
	//�ˏo�p�x��25�x
	m_light.spAngle = Math::DegToRad(25.0f);
}

void SkinModelRender::InitAmbientLight()
{
	//����
	m_light.ambientLight.x = 0.05f;
	m_light.ambientLight.y = 0.05f;
	m_light.ambientLight.z = 0.05f;
}

void SkinModelRender::InitHemiLight()
{
	//�n�ʐF�A�V���F�A�n�ʂ̖@���̃f�[�^��ݒ肷��
	m_light.groundColor.x = 0.7f;
	m_light.groundColor.y = 0.5f;
	m_light.groundColor.z = 0.3f;

	//�V���F��ݒ�
	m_light.skyColor.x = 0.15f;
	m_light.skyColor.y = 0.7f;
	m_light.skyColor.z = 0.95f;

	//�n�ʂ̖@����ݒ�
	m_light.groundNormal.x = 0.0f;
	m_light.groundNormal.y = 1.0f;
	m_light.groundNormal.z = 0.0f;
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