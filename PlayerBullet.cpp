#include "PlayerBullet.h"
#include <cassert>
#include "MatrixTrans.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) 
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

}


void PlayerBullet::Update() 
{
	 //worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	 worldTransform_.UpdateMatrix(); 

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{
	 model_->Draw(worldTransform_, viewProjection, ModeltextureHandle_);
}