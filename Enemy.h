#pragma once
#include "Model.h"
#include "WorldTransform.h"

enum class Phase
{
	Approach,
	Leave,
};

class Enemy
{
public:


	//初期化
	void Initialize(Model* model, uint32_t textureHandle);



	//更新処理
	void Update();



	//描画
	void Draw(ViewProjection& viewProjection);


	
private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// モデル
	Model* model_ = nullptr;

	uint32_t EnemytextureHandle_ = 0u;


	//フェーズ
	Phase phase_ = phase_;

};

