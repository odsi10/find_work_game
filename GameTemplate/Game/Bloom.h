#pragma once

//���N���X���C���N���[�h����
#include"GaussianBlur.h"

class Bloom : public IGameObject
{
public:	//�R���X�g���N�^���X
	Bloom();
	~Bloom();
	bool Start() ;
	void Update();

public:	//�����o�֐�
	//����������
	void Init();

	void DrawWait(RenderContext& renderContext);

	void DrawFinish(RenderContext& renderContext);

private:	//�f�[�^�����o
	RenderTarget m_mainRenderTarget;	// 32�r�b�g�̕��������_�̃J���[�o�b�t�@�[��ێ��������C�������_�����O�^�[�Q�b�g���쐬����
	RenderTarget m_luminnceRenderTarget;	// �P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
	Sprite m_luminanceSprite;
	GaussianBlur m_gaussianBlur[4];
	Sprite m_finalSprite;
	Sprite m_copyToFrameBufferSprite;
};

