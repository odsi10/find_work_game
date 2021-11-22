#pragma once

// �}�W�b�N�i���o�[�̍폜��
// �t�@�C���p�X��
// �Ǘ��ꏊ

namespace filePath	// �t�@�C���p�X
{
	namespace tkm	// ���f��
	{
		constexpr const char* UnityChan = "Assets/modelData/unityChan.tkm";		// �����f��
		constexpr const char* PlayerModel = "Assets/modelData/player.tkm";		// �v���C���[
		constexpr const char* EnemyModel = "Assets/modelData/enemy.tkm";		// �G�l�~�[
		constexpr const char* BackGround = "Assets/modelData/backGround.tkm";	//�X�e�[�W
	}

	namespace tka	// �A�j���[�V����
	{
		constexpr const char* Idle = "Assets/animData/idle.tka";	// ����
		constexpr const char* MoveForward = "Assets/animData/moveForward.tka";	// �O�i
	}
}

namespace findName	// FindGO�̂��߂̖��O�t��
{
	constexpr const char* BackGround = "�o�b�N�O���E���h";
	constexpr const char* Player = "�v���C���[";
	constexpr const char* GameCamera = "�Q�[���J����";
	constexpr const char* Enemy = "�G�l�~�[";
}

namespace priority	// �D��x
{
	const int PriorityZero = 0;
}