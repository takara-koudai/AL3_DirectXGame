#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"
#include"AxisIndicator.h"
#include <cassert>
#include "Scene.h"
#include "Player.h"

class TitleScene 
{
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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



	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGameScene; }
	SceneType Nextscene2() { return SceneType::kEndeScene; }


	//初期化用の関数
	void Reset() { isSceneEnd = false; }

	
private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;


	// ビュープロジェクション
	ViewProjection viewProjection_;

	//タイトルのテクスチャ
	uint32_t TitleTextureHandle = 0u;


	Sprite* titleSprite = nullptr;

	uint32_t start = 0;

	// シーン遷移
	bool isSceneEnd = false;

	//プレイヤー
	Player* player_ = nullptr;

	//初期化用変数

};
