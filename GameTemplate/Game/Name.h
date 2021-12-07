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
		constexpr const char* BackGround = "Assets/modelData/backGround.tkm";	// �X�e�[�W
	}

	namespace tka	// �A�j���[�V����
	{
		constexpr const char* Idle = "Assets/animData/idle.tka";										// ����
		constexpr const char* MoveForward = "Assets/animData/moveForward.tka";							// �O�i
		constexpr const char* MoveForwardSecondPower = "Assets/animData/moveForwardSecondPower.tka";	// �O�i�p���[2�i��
		constexpr const char* MoveForwardThirdPower = "Assets/animData/moveForwardThirdPower.tka";		// �O�i�p���[�R�i��
		constexpr const char* KnockBack = "Assets/animData/knockBack.tka";								// �m�b�N�o�b�N
	}
}

namespace findName	// FindGO�̂��߂̖��O�t��
{
	constexpr const char* BackGround = "�o�b�N�O���E���h";
	constexpr const char* Player = "�v���C���[";
	constexpr const char* GameCamera = "�Q�[���J����";
	constexpr const char* Enemy = "�G�l�~�[";
	constexpr const char* PlayerEnemyHit = "�v���C���[�G�l�~�[�q�b�g";
}

namespace priority	// �D��x
{
	const int PriorityZero = 0;
}

namespace constants // �萔
{
	const int IntZero = 0;
	const int IntOne = 1;
	const int IntTwo = 2;
	const int IntThree = 3;
}