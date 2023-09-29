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

class ClearScene 
{
public:


	/// <summary>
	/// コンストクラタ
	/// </summary>
	ClearScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ClearScene();

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
	//bool IsSceneEnd2() { return isSceneEnd2; }

	SceneType NextScene() { return SceneType::kTitle; }
	SceneType Nextscene2() { return SceneType::kEndeScene; }
	SceneType NextScene3() { return SceneType::kClearScene; }

	void Reset() { isSceneEnd = false; }
	//void Reset2() { isSceneEnd2 = false; }


private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// タイトルのテクスチャ
	uint32_t ClearTextureHandle = 0u;


	Sprite* clearSprite = nullptr;

	uint32_t start = 0;

	// シーン遷移
	bool isSceneEnd = false;
	//bool isSceneEnd2 = false;

};
