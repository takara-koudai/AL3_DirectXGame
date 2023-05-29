#include "PlayerBullet.h"
#include <cassert>
#include "MatrixTrans.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
{

	//NULLポインタチェック
	assert(model);

	model_ = model;

	//テクスチャ読み込み
	ModeltextureHandle_ = TextureManager::Load("black.png");

	//ワールドトランスフォーム初期化
	//worldTransform_.translation_ = {};

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;

}


void PlayerBullet::Update() 
{

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	
	worldTransform_.UpdateMatrix(); 

	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

}


void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{
	 model_->Draw(worldTransform_, viewProjection, ModeltextureHandle_);
}