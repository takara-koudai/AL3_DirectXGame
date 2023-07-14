#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"

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




private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0; //自機


	Model* model_ = nullptr;


	//ワールド変換
	WorldTransform worldTransform_;


	//ビュープロジェクション
	ViewProjection viewProjection_;


	//プレイヤー
	Player* player_ = nullptr;

	float inputFloat3[3] = {0, 0, 0};


	//デバッグカメラ
	bool isDebugCameraActive_ = false;


	DebugCamera* debugCamera_ = nullptr;


	//敵
	Enemy* enemy_ = nullptr;

	uint32_t EnemytextureHandle_ = 0; // 敵


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
