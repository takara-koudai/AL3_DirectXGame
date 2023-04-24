#include "Player.h"
#include <cassert>


//
//初期化
void Player::Initialize(Model* model, uint32_t textureHandle) { 

	//NULLポインタチェック
	assert(model);


	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//ワールド変換の初期化
	worldTransform_.Initialize();

}

//
//更新処理
void Player::Update()
{

	worldTransform_.TransferMatrix();

}



//
//描画
void Player::Draw(ViewProjection &viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}