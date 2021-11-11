#pragma once

// ���N���X���C���N���[�h����
#include <vector>
#include <Model.h>

#include "ModelRender.h"

// ���N���X���g�����߂ɐ錾����
class ModelRender;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	bool Start();
	void Update();

public:
	/// <summary>
	/// �e���f����������
	/// </summary>
	void Init();
	
	/// <summary>
	/// �e���f����o�^
	/// </summary>
	/// <param name="shdowModel"></param>
	void RegistModel(Model* shdowModel)
	{
		m_modelArray.push_back(shdowModel);
	}

	/// <summary>
	/// �e���f����`��
	/// </summary>
	/// <param name="renderContext"></param>
	void Draw(RenderContext& renderContext);

	void ShadowRenderTarget();

public:
	Camera& GetLightCamera()
	{
		return m_lightCamera;
	}

	RenderTarget& GetRenderTarget()	//�R�s�[�ɒ��ӁI�I�I
	{
		return m_shadowMap;
	}

private: //�f�[�^�����o
	ModelRender* m_modelRender = nullptr;

	// �e�`��p�̃��C�g�J�������쐬����
	Camera m_lightCamera;

	std::vector<Model*> m_modelArray;

	RenderTarget m_shadowMap;	//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g������������
};