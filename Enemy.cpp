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

	worldTransform_.translation_.z = 30.0f;

	phase_ = Phase::Approach;


}


void Enemy::Update()
{

	Vector3 move = {0.0, 0.0, 0.0f};

	const float kCharacterSpeed = 0.2f;


	switch (phase_) 
	{
	case Phase::Approach: // 接近フェーズ
	default:

		// 移動(ベクトルの加算)

		move.z -= kCharacterSpeed;

		//規定の位置に到達した離脱
		if (worldTransform_.translation_.z < 0.0f)
		{
			phase_ = Phase::Leave;
		}

		break;


	case Phase::Leave: // 離脱フェーズ

		// 移動(ベクトルの加算)
		
		move.x -= kCharacterSpeed;
		move.y += kCharacterSpeed;
		move.z -= kCharacterSpeed;

		break;
	}


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
