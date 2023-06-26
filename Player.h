#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>


class Player 
{
public:

	void Initialize(Model* model, uint32_t textureHandle);

	
	// 更新処理


	void Update();

	
	// 描画


	void Draw(ViewProjection &viewProjection);

	
	//攻撃
	void Attack(Vector3& position);

	
	//デストラクタ
	~Player();



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
