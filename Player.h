﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"


class Player {
public:

	void Initialize(Model* model, uint32_t textureHandle);

	
	// 更新処理


	void Update();

	
	// 描画
	


	void Draw(ViewProjection &viewProjection);

	

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	//モデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	
	//キーボード入力
	Input* input_ = nullptr;
	

};
