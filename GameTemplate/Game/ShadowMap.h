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
	void Init();

	void Drow(RenderContext& renderContext);
	/// <summary>
	/// �e���f����o�^
	/// </summary>
	/// <param name="shdowModel"></param>
	void RegistModel(Model* shdowModel)
	{
		m_modelArray.push_back(shdowModel);
	}

	void AddModel(Model& ShadowModel);

private:
	void ShadowRenderTarget();

private: //�f�[�^�����o
	ModelRender* m_modelRender = nullptr;

	std::vector<Model*> m_modelArray;

	RenderTarget m_shadowMap;	//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g������������
};