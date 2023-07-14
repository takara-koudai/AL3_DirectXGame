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

//自機クラスの前方宣言
class Player;


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


	//デストラクタ
	~Enemy();


	//弾発射間隔
	static const int kFireInterval = 50;
	

	//接近フェーズの初期化
	void Phase_();


	//setterの利用
	void SetPlayer(Player* player) { player_ = player; }


	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リスト
	const std::list<EnemyBullet*>& GetBullet() const { return Enemybullets_; }
	

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


	//自キャラ
	Player* player_ = nullptr;

	

};

