#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>
#include "Sprite.h"

class Player 
{
public:


	//初期化
	void Initialize(Model* model, uint32_t textureHandle, Vector3 Starpos);

	
	// 更新処理
	void Update(ViewProjection& viewProjection);

	
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


	// <summary>
	// UI描画
	// </summary>
	void DrawUI();


	//Vector3 GetWorldPosition() 
	//{
	//	// ワールド座標を入れる変数
	//	Vector3 worldPos;

	//	// ワールド行列の平行移動成分を取得(ワールド座標)
	//	worldPos.x = worldTransform_.matWorld_.m[3][0];
	//	worldPos.y = worldTransform_.matWorld_.m[3][1];
	//	worldPos.z = worldTransform_.matWorld_.m[3][2];

	//	return worldPos;
	//}
    

	// <summary>
	// レティクルUpdate
	// </summary>
	void UpdateReticle(ViewProjection& viewProjection);


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


	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;


	//2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;

	Vector2 ReticlePos = {640, 360};
	Vector4 color = {1, 1, 1, 1};
	Vector2 anchor = {0.5f, 0.5f};

	// マウス
	void GetmousePoint();

	void GetReticlePoint();
	
	POINT mausePosition;

	//ゲームパッド
	XINPUT_STATE joyState;
	Vector2 joyPos{640.0f, 360.f};


};
