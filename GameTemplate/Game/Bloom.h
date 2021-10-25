#pragma once

//���N���X���C���N���[�h����
#include"GaussianBlur.h"

class Bloom : public IGameObject
{
public:	//�R���X�g���N�^���X
	Bloom();
	~Bloom();
	bool Start() override final;
	void Update() override final;

public:	//�����o�֐�
	//����������
	void Init();

	void DrowWait(RenderContext& renderContext);

	void DrowFinish(RenderContext& renderContext);

private:	//�f�[�^�����o
	RenderTarget mainRenderTarget;	// 32�r�b�g�̕��������_�̃J���[�o�b�t�@�[��ێ��������C�������_�����O�^�[�Q�b�g���쐬����
	RenderTarget luminnceRenderTarget;	// �P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
	SpriteInitData luminanceSpriteInitData;
	Sprite luminanceSprite;
	GaussianBlur gaussianBlur[4];
	SpriteInitData finalSpriteInitData;
	Sprite finalSprite;
	SpriteInitData spriteInitData;
	Sprite copyToFrameBufferSprite;
};

