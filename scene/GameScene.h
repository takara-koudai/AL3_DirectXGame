#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "RailCamera.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// <summary>
	// 衝突判定と応答
	// </summary>
	void CheckAllCollisions();

	// Vector3 GetWorldPosition() { return worldTransform_.translation_; }

	// <summary>
	// 衝突判定と応答
	// </summary>
	void AddEnemyBullet(EnemyBullet* enemybullet);

	// <summary>
	// 敵発生データの読み込み
	// </summary>
	void LoadEnemyPopData();

	// <summary>
	// 敵発生コマンドの更新
	// </summary>
	void UpdateEnemyPopCommands();


	bool IsSceneEnd() { return isSceneEnd; }
	bool ClearScene() { return clearScene; }

	SceneType NextScene() { return SceneType::kEndeScene; }
	SceneType NextScene2() { return SceneType::kClearScene; }

	//ゲームオーバーのリセット
	void Reset() 
	{
		isSceneEnd = false;

		//敵リセット
		//enemies_.push_back(enemy_);
	}

	
	//クリアのリセット
	void ClearReset() 
	{
		clearScene = false;
		count = 0;
	}



	


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	void EnemySpawn(Vector3& position);
	void EnemyObjUpdate();
	void EnemyObjDraw();

	uint32_t textureHandle_ = 0; // 自機

	Model* model_ = nullptr;

	// ワールド変換
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// プレイヤー
	Player* player_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};

	// デバッグカメラ
	bool isDebugCameraActive_ = false;

	DebugCamera* debugCamera_ = nullptr;

	// 敵
	Enemy* enemy_ = nullptr;

	uint32_t EnemytextureHandle_ = 0; // 敵

	// 背景
	Skydome* skydome_ = nullptr;

	Model* skydomeModel_ = nullptr;

	RailCamera* railCamera = nullptr;

	// 敵と弾のリスト
	std::list<EnemyBullet*> enemyBullets_;
	std::list<Enemy*> enemies_;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	// 待機用のタイマーとフラグ
	bool waitFlag_ = false;
	int32_t waitTime_ = 0;


	// シーン遷移
	//ゲームオーバー
	bool isSceneEnd = false;

	//クリア
	bool clearScene = false;

	int count = 0;




	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
