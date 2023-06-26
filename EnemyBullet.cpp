#include "EnemyBullet.h"
#include <cassert>
#include "MatrixTrans.h"


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULLポインタチェック
	assert(model);

	model_ = model;


	//テクスチャ読み込み
	EnemyBulletHandle_ = TextureManager::Load("RED.png");


	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;

}

void EnemyBullet::Update()
{

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) 
	{
		isDead_ = true;
	}

}



void EnemyBullet::Draw(const ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, EnemyBulletHandle_);

}