#pragma once
#include "Model.h"
#include "WorldTransform.h"

class PlayerBullet
{
public:

	//
	//初期化

	void Initialize(Model* model, const Vector3& position);

	//
	//更新処理

	void Update();


	//
	//描画

	void Draw(const ViewProjection& viewProjection);


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


	// モデル
	Model* model_ = nullptr;
	

	// テクスチャハンドル
	uint32_t ModeltextureHandle_ = 0u;



};