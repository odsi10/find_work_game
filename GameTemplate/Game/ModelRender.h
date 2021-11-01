#pragma once
// ���N���X���C���N���[�h����
#include <Model.h>

//���̃N���X���C���N���[�h����
#include "Name.h"
#include "ShadowMap.h"

// ���N���X���g�����߂ɐ錾����
class ShadowMap;

const int NUM_DIRECTIONAL_LIGHT = 4; // �f�B���N�V�������C�g�̐�

//���C�g�p�̍\���̂��`����
struct Light {
	//�f�B���N�V�������C�g
	Vector3 dirDirection; //���C�g�̕���
	//HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁A
	//C++���ɂ̓p�f�B���O�𖄂߂Ă����B
	float dirPad;
	Vector3 dirColor;
	float colPad;

	//�|�C���g���C�g
	Vector3 ptPosition; //�ʒu
	float ptPad;		//�p�f�B���O
	Vector3 ptColor;	//�J���[
	float ptRange;		//�e���͈�

	//�X�|�b�g���C�g
	Vector3 spPosition;		//�ʒu
	float spPad;			//�p�f�B���O
	Vector3 spColor;		//�J���[
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x

	//�\���̂Ɏ��_�̈ʒu��ǉ�����
	Vector3 eyePos; //���_�̈ʒu
	float eyePad;   //�p�f�B���O

	//����
	Vector3 ambientLight;   // �A���r�G���g���C�g
	float ambPad;			//�p�f�B���O

	//�������C�g
	Vector3 groundColor;	//�n�ʐF
	float groPad;			//�p�f�B���O
	Vector3 skyColor;		//�V���F
	float skyPad;			//�p�f�B���O
	Vector3 groundNormal;	//�n�ʂ̖@��
};



class ModelRender : public IGameObject
{
public:
	ModelRender();
	~ModelRender();
	bool Start(ShadowMap& shadowMap) override final;
	void Update() override final;
	void Render(RenderContext& renderContext) override final;



public:
	/**
	 * @brief �������֐�
	 * @param filePath tkm�t�@�C���̃t�@�C���p�X
	*/
	//void Init(const char* filePath);


	void Init(const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ/*,
		AnimationClip* animationClip = nullptr,
		int maxAnimationClipNum = 0*/
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
	void InitPointLight();     //�|�C���g���C�g
	void InitSpotLight();      //�X�|�b�g���C�g
	void InitAmbientLight();   //����
	void InitHemiLight();      //�������C�g

	bool InitSkeleton(const char* filePath);

	/**
	 * @brief �A�j���[�V�����̏�����
	 * @param animationClip �A�j���[�V�����N���b�v
	 * @param maxAnimationClipNum �A�j���[�V�����N���b�v�̑���
	*/
	void InitAnimation(AnimationClip* animationClip, int maxAnimationClipNum);

	void InitShadowModel();

public:
	/**
	 * @brief �A�j���[�V�������Đ�����
	 * @param animationNumber �o�^���Ă���A�j���[�V�����N���b�v�̔ԍ�
	 * @param interpolateTime �⊮���ԁi�P�ʁF�b�j
	*/
	void PlayAnimation(int animationNumber, float interpolateTime = 0.2f)
	{
		m_animationPointer->Play(animationNumber, interpolateTime);
	}

	/**
	 * @brief �A�j���[�V�������Đ�����
	 * @return �Đ���
	*/
	const bool IsPlayingAnimation() const
	{
		return m_animationPointer->IsPlaying();
	}

	bool IsInited() const
	{
		return m_animationPointer->IsInited();
	}



public: //Get�֐�

	const Vector3 GetPosition()
	{
		return m_position;
	}

	const Quaternion GetRotation()
	{
		return m_rotation;
	}

	const Vector3 GetScale()
	{
		return m_scale;
	}

	Model Getmodel()
	{
		m_ShadowModel;
	}

public: //Set�֐�

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	void UpPositionY(const float upY)
	{
		m_position.y += upY;
	}

	void DownPositionY(const float downY)
	{
		m_position.y -= downY;
	}

	void ResetPositionY()
	{
		m_position.y = 0.0f;
	}

	void SetRotation(const Quaternion rotation)
	{
		m_rotation = rotation;
	}

	void SetRotationX(const float rotX) {
		m_rotation.SetRotationX(rotX);
	}

	void SetRotationDegY(const float rotY) {
		m_rotation.SetRotationDegY(rotY);
	}

	void SetScale(const Vector3 scale)
	{
		m_scale = scale;
	}

private: //data menber
	Model m_model;	//���f��
	std::unique_ptr<Skeleton> m_skeletonPointer; //�X�P���g���̃|�C���^�[
	std::unique_ptr<Animation> m_animationPointer; //�A�j���[�V�����̃|�C���^�[

	const char* m_tkmFilePath = nullptr; //tkm�t�@�C���̃t�@�C���p�X
	Light m_light;						 //���C�g

	Vector3 m_position = g_vec3Zero;			//�ʒu
	Quaternion m_rotation = g_quatIdentity;		//��]
	Vector3 m_scale = g_vec3One;				//�g��

	bool m_finishInit = false; //���������I�������

	ModelInitData m_shadowModelInitData; //�V���h�E�}�b�v�ɕ`�悷�郂�f��������������
	Model m_ShadowModel;	//�V���h�E�p�̃��f��������������

	ShadowMap* m_shadowMap = nullptr;
};