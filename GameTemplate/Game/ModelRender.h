#pragma once
// ���N���X���C���N���[�h����
#include <Model.h>

#include "Name.h"
#include "ShadowMap.h"
#include "AnimationClip.h"

// ���N���X���g�����߂ɐ錾����
class ShadowMap;
class AnimationClip;

//const int NUM_DIRECTIONAL_LIGHT = 4; // �f�B���N�V�������C�g�̐�

// ���C�g�p�̍\���̂��`����
struct Light {
	// �f�B���N�V�������C�g
	Vector3 dirDirection; //���C�g�̕���
	// HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁A
	// C++���ɂ̓p�f�B���O�𖄂߂Ă����B
	float dirPad;
	Vector3 dirColor;
	float colPad;

	// �|�C���g���C�g
	Vector3 ptPosition; //�ʒu
	float ptPad;		//�p�f�B���O
	Vector3 ptColor;	//�J���[
	float ptRange;		//�e���͈�

	// �X�|�b�g���C�g
	Vector3 spPosition;		//�ʒu
	float spPad;			//�p�f�B���O
	Vector3 spColor;		//�J���[
	float spRange;			//�e���͈�
	Vector3 spDirection;	//�ˏo����
	float spAngle;			//�ˏo�p�x

	// �\���̂Ɏ��_�̈ʒu��ǉ�����
	Vector3 eyePos; //���_�̈ʒu
	float eyePad;   //�p�f�B���O

	// ����
	Vector3 ambientLight;   // �A���r�G���g���C�g
	float ambPad;			//�p�f�B���O

	// �������C�g
	Vector3 groundColor;	//�n�ʐF
	float groPad;			//�p�f�B���O
	Vector3 skyColor;		//�V���F
	float skyPad;			//�p�f�B���O
	Vector3 groundNormal;	//�n�ʂ̖@��
};



class ModelRender : public IGameObject
{
public:	// �R���X�g���N�^���X
	ModelRender();
	~ModelRender();
	bool Start(ShadowMap* shadowMap) override final;
	void Update();
	void Render(RenderContext& renderContext) override final;

public:
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="shadowMap">�V���h�E�}�b�v</param>
	/// <param name="modelUpAxis">���f���̏����</param>
	/// <param name="animationClip">�A�j���[�V�����N���b�v</param>
	/// <param name="maxAnimationClipNum">�A�j���[�V�����N���b�v�̑���</param>
	void Init(const char* filePath,
		ShadowMap& shadowMap,
		enModelUpAxis::EnModelUpAxis modelUpAxis = enModelUpAxis::enModelUpAxisZ,
		AnimationClip * animationClip = nullptr,
		int maxAnimationClipNum = 0
	);

private:
	/// <summary>
	/// �f�B���N�V�������C�g
	/// </summary>
	void InitDirectionLight();
	/// <summary>
	/// �|�C���g���C�g
	/// </summary>
	void InitPointLight();
	/// <summary>
	/// �X�|�b�g���C�g
	/// </summary>
	void InitSpotLight();
	/// <summary>
	/// ����
	/// </summary>
	void InitAmbientLight();
	/// <summary>
	/// �������C�g
	/// </summary>
	void InitHemiLight();

	/// <summary>
	/// �X�P���g���̏�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <returns></returns>
	bool InitSkeleton(const char* filePath);

	/**
	 * @brief �A�j���[�V�����̏�����
	 * @param animationClip �A�j���[�V�����N���b�v
	 * @param maxAnimationClipNum �A�j���[�V�����N���b�v�̑���
	*/
	void InitAnimation(AnimationClip* animationClip, int maxAnimationClipNum);

	/// <summary>
	/// �V���h�E�̏�������
	/// </summary>
	/// <param name="shadowMap">�V���h�E�}�b�v</param>
	void InitShadowModel(ShadowMap* shadowMap);

	/// <summary>
	/// �e�����Ƃ���郂�f��������������i����͂��ׂĉe�����Ƃ���郂�f���j
	/// </summary>
	/// <param name="shadowMap">�V���h�E�}�b�v</param>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="modelUpAxis">���f���̏����</param>
	void InitShadowReceiver(
		ShadowMap* shadowMap,
		const char* filePath,
		enModelUpAxis::EnModelUpAxis modelUpAxis
	);

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

public: // Get�֐�

	/// <summary>
	/// ���f���̈ʒu���擾�ł���
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// ���f���̉�]���擾�ł���
	/// </summary>
	/// <returns></returns>
	const Quaternion GetRotation()
	{
		return m_rotation;
	}

	/// <summary>
	/// ���f���̊g��A�k�����擾�ł���
	/// </summary>
	/// <returns></returns>
	const Vector3 GetScale()
	{
		return m_scale;
	}

	/// <summary>
	/// ���f���̃A�h���X���擾�ł���
	/// </summary>
	/// <returns></returns>
	Model& GetModel()
	{
		return m_model;
	}

	

public: // Set�֐�
	/// <summary>
	/// ���f���̈ʒu���w��ł���
	/// </summary>
	/// <param name="position">�ʒu</param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// ���f���̉�]���w��ł���
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion rotation)
	{
		m_rotation = rotation;
	}

private: //	�f�[�^�����o
	Model m_model;						 // ���f��
	ModelInitData m_modelInitData;		 // ���f���̏��������邽�߂̏���ݒ�
	ModelInitData m_shadowModelInitData; // �V���h�E�}�b�v�ɕ`�悷�郂�f��������������
	Model m_ShadowModel;				 // �V���h�E�p�̃��f��������������
	ShadowMap* m_shadowMap = nullptr;	 // �V���h�E�}�b�v
	Light m_light;						 // ���C�g

	std::unique_ptr<Skeleton> m_skeletonPointer;	// �X�P���g���̃|�C���^�[
	std::unique_ptr<Animation> m_animationPointer;  // �A�j���[�V�����̃|�C���^�[

	Vector3 m_position = g_vec3Zero;			// �ʒu
	Quaternion m_rotation = g_quatIdentity;		// ��]
	Vector3 m_scale = g_vec3One;				// �g��

	const char* m_tkmFilePath = nullptr; // tkm�t�@�C���̃t�@�C���p�X
	
	bool m_initSkeleton = false;		 // �X�P���g���̏����������ꂽ��
	bool m_finishInit = false;			 // ���������I�������
};