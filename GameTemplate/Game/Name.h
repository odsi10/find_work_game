#pragma once

// マジックナンバーの削除や
// ファイルパスの
// 管理場所

namespace filePath	// ファイルパス
{
	namespace tkm	// モデル
	{
		constexpr const char* UnityChan = "Assets/modelData/unityChan.tkm";		// 仮モデル
		constexpr const char* PlayerModel = "Assets/modelData/player.tkm";		// プレイヤー
		constexpr const char* EnemyModel = "Assets/modelData/enemy.tkm";		// エネミー
		constexpr const char* BackGround = "Assets/modelData/backGround.tkm";	//ステージ
	}

	namespace tka	// アニメーション
	{
		constexpr const char* Idle = "Assets/animData/idle.tka";	// 立ち
		constexpr const char* MoveForward = "Assets/animData/moveForward.tka";	// 前進
	}
}

namespace findName	// FindGOのための名前付け
{
	constexpr const char* BackGround = "バックグラウンド";
	constexpr const char* Player = "プレイヤー";
	constexpr const char* GameCamera = "ゲームカメラ";
	constexpr const char* Enemy = "エネミー";
}

namespace priority	// 優先度
{
	const int PriorityZero = 0;
}