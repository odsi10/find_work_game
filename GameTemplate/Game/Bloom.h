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
	RootSignature rs;
	RenderTarget mainRenderTarget;
	RenderTarget luminnceRenderTarget;
	SpriteInitData luminanceSpriteInitData;
	Sprite luminanceSprite;
	GaussianBlur gaussianBlur[4];
	SpriteInitData finalSpriteInitData;
	Sprite finalSprite;
	SpriteInitData spriteInitData;
	Sprite copyToFrameBufferSprite;
};

