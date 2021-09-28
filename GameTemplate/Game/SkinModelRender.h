#pragma once

//���N���X���C���N���[�h����
#include<Model.h>

#include"Name.h"

//���C�g�p�̍\���̂��`����B
struct Light {
	//�f�B���N�V�������C�g
	Vector3 ligDirection;	//���C�g�̕���
	//HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���
	//16�̔{���̃A�h���X�ɔz�u����邽�߁A
	//C++���ɂ̓p�f�B���O�𖄂߂Ă����B
	float dirPad;
	Vector3 ligColor;	//���C�g�̃J���[�B

	//�g�U����
	//�\���̂Ɏ��_�̈ʒu��ǉ�����
	Vector3 eyePos; //���_�̈ʒu
	float eyePad;

	//����
	Vector3 ambientLight;   // �A���r�G���g���C�g
	float ambiPad;
};

class SkinModelRender : public IGameObject
{
public:	//�R���X�g���N�^���X
	SkinModelRender();
	~SkinModelRender();
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& renderContext) override final;

public:
	/**
	 * @brief �������֐�
	 * @param filePath tkm�t�@�C���̃t�@�C���p�X
	*/
	void Init(const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ
	);

private:
	/**
	 * @brief ���f���̏�����
	 * @param filePath tkm�t�@�C���̃t�@�C���p�X
	*/
	void InitModel(const char* filePath,
		enModelUpAxis::EnModelUpAxis = enModelUpAxis::enModelUpAxisZ
	);

	void InitDirectionLight(); //�f�B���N�V�������C�g
	void InitPointLight(); //�|�C���g���C�g
	void InitSpotLight(); //�X�|�b�g���C�g
	void InitAmbientLight(); //����
	void InitHemiLight(); //�������C�g

private: //�f�[�^�����o
	Model m_model;

	const char* m_tkmFilePath = nullptr; //tkm�t�@�C���̃t�@�C���p�X

	Light m_light;	//���C�g

	Vector3 m_position = g_vec3Zero;			//�ʒu
	Quaternion m_rotation = g_quatIdentity;		//��]
	Vector3 m_scale = g_vec3One;				//�g��

	bool m_finishInit = false; //���������I�������
};