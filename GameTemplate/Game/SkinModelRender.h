#pragma once

//���N���X���C���N���[�h����
#include<Model.h>

#include"Name.h"

//���C�g�p�̍\���̂��`����
struct Light {
	//�f�B���N�V�������C�g
	Vector3 dirDirection; //���C�g�̕���
	//C++���ɂ̓p�f�B���O�𖄂߂Ă����B
	float pad;
	Vector3 dirColor;
	float dirPad;

	//�|�C���g���C�g
	Vector3 ptPosition; //�ʒu
	float ptPad;			//�p�f�B���O
	Vector3 ptColor;	//�J���[
	float ptRange;		//�e���͈�

	//�X�|�b�g���C�g
	Vector3 spPosition;		//�ʒu
	float spPad;				//�p�f�B���O
	Vector3 spColor;		//�J���[
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x

	//�\���̂Ɏ��_�̈ʒu��ǉ�����
	Vector3 eyePos; //���_�̈ʒu
	float eyePad;

	//����
	Vector3 ambientLight;   // �A���r�G���g���C�g
	float ambPad;

	//�������C�g
	Vector3 groundColor;	//�n�ʐF
	float groPad;
	Vector3 skyColor;		//�V���F
	float skyPad;
	Vector3 groundNormal;	//�n�ʂ̖@��
};

class SkinModelRender : public IGameObject
{
public:
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

	Light m_light;

	Vector3 m_position = g_vec3Zero;			//�ʒu
	Quaternion m_rotation = g_quatIdentity;		//��]
	Vector3 m_scale = g_vec3One;				//�g��

	bool m_finishInit = false; //���������I�������
};