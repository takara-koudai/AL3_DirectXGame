#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "AxisIndicator.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "MatrixTrans.h"
#include "Skydome.h"
#include "RailCamera.h"

GameScene::GameScene() {}

GameScene::~GameScene()
{ 
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete skydomeModel_;
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//自機
	textureHandle_ = TextureManager::Load("mario.jpg");
	//textureHandle_ = TextureManager::Load("debugfont.png");


	//敵
	EnemytextureHandle_ = TextureManager::Load("jugemu.jpg");


	//背景
	skydomeModel_ = Model::CreateFromOBJ("skydome", true);


	//ビュープロジェクションの初期化
	viewProjection_.farZ = 1000.0f;


	//model_ = Model::Create();

	worldTransform_.Initialize();


	viewProjection_.Initialize();


	//
	//プレイヤー
	//


	model_ = Model::Create();


	//自キャラの生成
	player_ = new Player();
	

	//自キャラの初期化
	Vector3 playerPosition(0, 0, 15.0f);
	player_->Initialize(model_,textureHandle_,playerPosition);



	//敵キャラの初期化
	enemy_ = new Enemy();

	enemy_->Initialize(model_, EnemytextureHandle_);


	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);


	//背景
	skydome_ = new Skydome();
	
	skydome_->Initialize(skydomeModel_);


	//レールカメラ
	railCamera = new RailCamera();

	Vector3 radian = {0.0f, 0.0f, 0.0f};

	railCamera->Initialize(player_->GetWorldPosition(),radian);


	//自キャラとレールカメラの親子関係を結ぶ
	player_->SetPrent(&railCamera->GetWorldTransform());


	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

}

void GameScene::CheckAllCollisions()
{
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullet();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullet();

	//自キャラと敵弾の当たり判定
	#pragma region

	//自キャラの座標
	posA = player_->GetWorldPosition();


	//自キャラと敵弾の当たり判定
	for (EnemyBullet* bullet : enemyBullets)
	{
		//敵弾の座標
		posB = bullet->GetWorldPosition();

		float dx;
		float dy;
		float dz;
		float distance;
		float radius = 0.5f;


		// 座標AとBの距離を求める
		dx = (posB.x - posA.x) * (posB.x - posA.x);
		dy = (posB.y - posA.y) * (posB.y - posA.y);
		dz = (posB.z - posA.z) * (posB.z - posA.z);
		
		distance = dx + dy + dz;

		//球と球の交差判定
		if (distance <= (radius + radius) * (radius + radius))
		{
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();

			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

	#pragma endregion

	//自弾と敵キャラの当たり判定
	#pragma region

	Vector3 PosA, PosB;

	PosA = enemy_->GetWorldPosition();

	for (PlayerBullet* playerbullet : playerBullets)
	{
		//自弾の座標
		PosB = playerbullet->GetWorldPosition();

		float Dx;
		float Dy;
		float Dz;
		float distance2;
		float radius2 = 0.5;

		//距離を求める
		Dx = (PosB.x - PosA.x) * (PosB.x - PosA.x);
		Dy = (PosB.y - PosA.y) * (PosB.y - PosA.y);
		Dz = (PosB.z - PosA.z) * (PosB.z - PosA.z);

		distance2 = Dx + Dy + Dz;

		if (distance2 <= (radius2 + radius2) * (radius2 + radius2))
		{
			enemy_->OnCollision();

			playerbullet->OnCollision();
		}
	}

	#pragma endregion

	//自弾と敵弾の当たり判定
	#pragma region

	Vector3 BulletposA, BulletposB;

	for (PlayerBullet* BulletPlayer : playerBullets)
	{
		BulletposA = BulletPlayer->GetWorldPosition();

		for (EnemyBullet* BulletEnemy : enemyBullets)
		{
			BulletposB = BulletEnemy->GetWorldPosition();

			float dX;
			float dY;
			float dZ;
			float distance3;
			float radius3 = 0.5;

			dX = (BulletposB.x - BulletposA.x) * (BulletposB.x - BulletposA.x);
			dY = (BulletposB.y - BulletposA.y) * (BulletposB.y - BulletposA.y);
			dZ = (BulletposB.z - BulletposA.z) * (BulletposB.z - BulletposA.z);

			distance3 = dX + dY + dZ;

			if (distance3 <= (radius3 + radius3) * (radius3 + radius3))
			{
				BulletEnemy->OnCollision();

				BulletPlayer->OnCollision();
			}

		}

	}


	#pragma endregion

}


void GameScene::Update() 
{
	
	//自キャラの更新
	player_->Update();
	enemy_->Update();
	skydome_->Update();

	debugCamera_->Update();

	railCamera->Update();

	

	// 当たり判定
	CheckAllCollisions();

	//isDebugCameraActive_ = false;


	#ifdef _DEBUG

	if (input_->TriggerKey(DIK_P) == isDebugCameraActive_ == false)
	{
		isDebugCameraActive_ = true;

	} else if (input_->TriggerKey(DIK_P) == isDebugCameraActive_ == true) 
	{
		isDebugCameraActive_ = false;
	}

	

#endif // DEBUG
	

	// Cameraの処理
	if (isDebugCameraActive_) 
	{

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} 
	else 
	{

		viewProjection_.matView = railCamera->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		//ビュープロジェクション行列の更新と転送
		//viewProjection_.UpdateMatrix();
	}
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>.
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	
	skydome_->Draw(viewProjection_);

	
	//自キャラの描画
	
	player_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
