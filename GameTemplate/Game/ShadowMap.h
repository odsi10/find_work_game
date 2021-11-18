#pragma once

// ���N���X���C���N���[�h����
#include <vector>
#include <Model.h>

#include "ModelRender.h"
#include "GaussianBlur.h"

// ���N���X���g�����߂ɐ錾����
class ModelRender;
class GaussianBlur;

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

private:
	/// <summary>
	/// �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g�̏�����
	/// </summary>
	void InitShadowRenderTarget();

	/// <summary>
	/// �K�E�V�A���u���[�̏�����
	/// </summary>
	void InitGaussianBlur();

public:
	/// <summary>
	/// ���C�g�J�����̃Q�b�^�[
	/// </summary>
	/// <returns>���C�g�J����</returns>
	Camera& GetLightCamera()
	{
		return m_lightCamera;
	}

	/// <summary>
	/// �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	RenderTarget& GetShadowMapRenderTarget()	// &�Ȃ��̃N���X�̃R�s�[�ɒ��ӁI�I�I�A�h���X��n����
	{
		return m_shadowMapRenderTarget;
	}

private: //�f�[�^�����o
	ModelRender* m_modelRender = nullptr;

	// �e�`��p�̃��C�g�J�������쐬����
	Camera m_lightCamera;

	GaussianBlur m_gaussianBlur;

	std::vector<Model*> m_modelArray;

	RenderTarget m_shadowMapRenderTarget;	// �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g������������[
};