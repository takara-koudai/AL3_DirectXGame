#include "Player.h"
#include <cassert>
#include "MatrixTrans.h"
#include "ImGuiManager.h"


//
//初期化
void Player::Initialize(Model* model, uint32_t textureHandle) { 

	//NULLポインタチェック
	assert(model);


	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;


	// キーボード
	input_ = Input::GetInstance();


	//スケーリング
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};


	//回転
	//worldTransform_.rotation_ = {0.0f, 3.14f / 4.0f, 0.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	//平行移動行列
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	
	// ワールド変換の初期化
	worldTransform_.Initialize();
}


//
//更新処理
void Player::Update() 
{	

	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_LEFT)) 
	{
		move.x -= kCharacterSpeed;

	} else if (input_->PushKey(DIK_RIGHT)) 
	{
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_UP)) 
	{
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) 
	{
		move.y -= kCharacterSpeed;
	}


	//自機の旋回
	if (input_->PushKey(DIK_D))
	{
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	
	if (input_->PushKey(DIK_A)) 
	{
		worldTransform_.rotation_.y += kRotSpeed;
	}



	//移動限界座標
	const float kMoveLimitX = (35.0f);
	const float kMoveLimitY = (18.0f);


	//範囲を越えない処理

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);


	//キャラクター攻撃処理
	Attack(worldTransform_.translation_);


	//弾更新
	if (bullet_)
	{
		bullet_->Update();
	}

	

	//足し算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	
	

	worldTransform_.matWorld_ = 
	MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();


	//デバック画面
	/*ImGui::Begin("Debug");

	float playerPos[] = 
	{
	    worldTransform_.translation_.x, 
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z
	};
	ImGui::SliderFloat3("PlayerPos", playerPos, 1000, 720);



	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.x = playerPos[1];
	worldTransform_.translation_.x = playerPos[2];

	ImGui::End();*/


}


void Player::Attack(Vector3& position)
{
	
	if (input_->TriggerKey(DIK_SPACE))
	{

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, position);

		// 弾を登録する
		bullet_ = newBullet;
	}
	
}


//
//描画
void Player::Draw(ViewProjection &viewProjection)
{ 

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	if (bullet_)
	{
		bullet_->Draw(viewProjection);
	}
	
}