#include "Enemy.h"
#include "MatrixTrans.h"
#include <cassert>


void Enemy::Initialize(Model* model, uint32_t textureHandle)
{ 
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	EnemytextureHandle_ = textureHandle;


	worldTransform_.Initialize();

}


void Enemy::Update()
{

	Vector3 move = {0, 0.01, -0.2f};
	

	// 足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);


	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}


void Enemy::Draw(ViewProjection& viewProjection) 
{

	model_->Draw(worldTransform_, viewProjection, EnemytextureHandle_);

}
