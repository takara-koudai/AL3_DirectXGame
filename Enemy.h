#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>

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


	// 弾発射
	void Fire(Vector3& position_);


	~Enemy();


	static const int kFireInterval = 60;
	

	//接近フェーズの初期化
	void Phase_();


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// モデル
	Model* model_ = nullptr;

	uint32_t EnemytextureHandle_ = 0u;
	

	//フェーズ
	Phase phase_ = phase_;

	// 弾
	EnemyBullet* Enemybullet_ = nullptr;

	// 弾
	std::list<EnemyBullet*> Enemybullets_;


	//発射タイマー
	int32_t fireTimer = 0;

};

