#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>

class Player 
{
public:


	//初期化
	void Initialize(Model* model, uint32_t textureHandle, Vector3 Starpos);

	
	// 更新処理
	void Update();

	
	// 描画
	void Draw(ViewProjection &viewProjection);

	
	//攻撃
	void Attack(Vector3& position);

	
	//デストラクタ
	~Player();


	// ワールド座標を取得
	 Vector3 GetWorldPosition(){ return worldTransform_.translation_; }
	

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();


	//弾リスト
	const std::list<PlayerBullet*>& GetBullet() const { return bullets_; }


	//親となるワールドトランスフォームをセット
	void SetPrent(const WorldTransform* parent);



private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


	//モデル
	Model* model_ = nullptr;


	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	
	//キーボード入力
	Input* input_ = nullptr;


	// 弾
	PlayerBullet* bullet_ = nullptr;
	

	//弾
	std:: list<PlayerBullet*> bullets_;


	


};
