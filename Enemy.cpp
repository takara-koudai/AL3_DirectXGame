#include "Enemy.h"
//#include "EnemyBullet.h"
#include "MatrixTrans.h"
#include <cassert>

Enemy::~Enemy()
{
	for (EnemyBullet* Enemybullet : Enemybullets_)
	{
		delete Enemybullet_;
	}
}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	EnemytextureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.translation_.z = 50.0f;
	worldTransform_.translation_.x = 30.0f;

	phase_ = Phase::Approach;

	Phase_();
}

void Enemy::Fire(Vector3& position_) 
{

	// 弾の速度
	const float kBulletSpeed = -2.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newEnemyBullet = new EnemyBullet();
	newEnemyBullet->Initialize(model_, position_, velocity);

	// 弾を登録する
    //Enemybullet_ = newEnemyBullet;
	

	Enemybullets_.push_back(newEnemyBullet);
}

// 接近フェーズ関数
void Enemy::Phase_()
{
	// 発射タイマーを初期化
	fireTimer = kFireInterval;
}

void Enemy::Update()
{

	Vector3 move = {0.0, 0.0, 0.0f};

	const float kCharacterSpeed = 0.2f;

	switch (phase_) {
	case Phase::Approach: // 接近フェーズ
	default:

		// 移動(ベクトルの加算)
		move.z -= kCharacterSpeed;
		
		//
		//EnemyのUpdateを呼ぶ
		

		// 敵の攻撃処理
		// 発射タイマーカウントダウン
		fireTimer--;
		

		// 指定時間に達した
		if (fireTimer <= 0)
		{

			// 弾を発射
			Fire(worldTransform_.translation_);

			//Enemybullet_->Update();
			for (EnemyBullet* bullet : Enemybullets_) 
			{
				bullet->Update();
			}
			

			// 発射タイマーを初期化
			fireTimer = kFireInterval;

		}

		// 規定の位置に到達した離脱
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

	// デスフラグが立った弾を削除
	Enemybullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}

		return false;
	});
	

	for (EnemyBullet* bullet : Enemybullets_) 
	{
		bullet->Update();
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

	// 弾の描画
	for (EnemyBullet* Enemybullet : Enemybullets_)
	{
		Enemybullet->Draw(viewProjection);
	}

	if (Enemybullet_)
	{
		Enemybullet_->Draw(viewProjection);
	}

}
