#pragma once

// ���N���X���C���N���[�h����
#include <vector>
#include <Model.h>

#include "ModelRender.h"
#include "GaussianBlur.h"

// ���N���X���g�����߂ɐ錾����
class GaussianBlur;

// GPU���ŗ��p����V���h�E�p�̍\���̂��`����
struct ShadowParam
{
	Matrix m_mLVP;		// ���C�g�r���[�v���W�F�N�V�����s��
	Vector3 m_lightPos;	// ���C�g�J�����̍��W
};

class ShadowMap
{
public:	//�R���X�g���N�^���X
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
	Camera m_lightCamera;					// �e�`��p�̃��C�g�J�������쐬����

	GaussianBlur m_gaussianBlur;			// �K�E�V�A���u���[

	std::vector<Model*> m_modelArray;		// �e���f���̓o�^

	RenderTarget m_shadowMapRenderTarget;	// �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g������������
};