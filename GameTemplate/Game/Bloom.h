#pragma once

// ���N���X���C���N���[�h����
#include"GaussianBlur.h"

class Bloom
{
public:	// �R���X�g���N�^���X
	Bloom();
	~Bloom();
	bool Start() ;
	void Update();

public:	// �����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Init();

	/// <summary>
	/// �����_�����O�^�[�Q�b�g���p
	/// </summary>
	/// <param name="renderContext"></param>
	void DrawWait(RenderContext& renderContext);

	/// <summary>
	/// �ŏI�H��
	/// </summary>
	/// <param name="renderContext"></param>
	void DrawFinish(RenderContext& renderContext);

private:	//�f�[�^�����o
	RenderTarget m_mainRenderTarget;		// 32�r�b�g�̕��������_�̃J���[�o�b�t�@�[��ێ��������C�������_�����O�^�[�Q�b�g���쐬����
	RenderTarget m_luminnceRenderTarget;	// �P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
	Sprite m_luminanceSprite;				// �쐬�����������������ƂɃX�v���C�g������������B
	GaussianBlur m_gaussianBlur[4];			// �K�E�V�A���u���[��������
	Sprite m_finalSprite;					// �������������ɉ��Z�����p�̃X�v���C�g������������B
	Sprite m_copyToFrameBufferSprite;		// ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
};

