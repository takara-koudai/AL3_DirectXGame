#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() 
{ 
	delete sprite_; 
	delete model_;
	delete dedugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//textureHandle_ = TextureManager::Load("ikacahn.png");

	textureHandle_ = TextureManager::Load("mario.jpg");

	sprite_ = Sprite::Create(textureHandle_,{10, 10});


	//真ん中のマリオ
	model_ = Model::Create();

	worldTransform_.Initialize();

	viewProjection_.Initialize();

	//音声
	//
	soundDataHandle_ = audio_->LoadWave("fanfare.wav");

	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
	audio_->PlayWave(soundDataHandle_);


	//ライン描画
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);


	//デバックカメラ
	dedugCamera_ = new DebugCamera(1280, 720);


	//軸方向表示の使用
	AxisIndicator::GetInstance()->SetVisible(true);

	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&dedugCamera_->GetViewProjection());



}

void GameScene::Update() 
{ 
	//座標を取得
	 Vector2 position = sprite_->GetPosition(); 
	
	//移動させる
	position.x += 1.0f;
	position.y += 2.0f;
	
	sprite_->SetPosition(position);
	
	

	//音声操作

	if (input_->TriggerKey(DIK_SPACE)) 
	{
		//音声停止
		audio_->StopWave(voiceHandle_);

	}


	//ウィンドウ
	

	//始まり
	ImGui::Begin("Debug1");
	//入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);

	//float3スライダー
	ImGui::SliderFloat3("SilderFloat3", inputFloat3, 0.0f, 1.0f);

	//ImGui::Text("tanaka koudai %d.%d.%d", 2023, 04, 17);

	//終わり
	ImGui::End();

	//デモウィンドウの表示
	ImGui::ShowDemoWindow();


	//デバックカメラ
	dedugCamera_->Update();


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

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	//真ん中のマリオ
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);


	//3D回転
	model_->Draw(worldTransform_, dedugCamera_->GetViewProjection(), textureHandle_);


	PrimitiveDrawer::GetInstance()->DrawLine3d({10, 0, 0}, {1, 0, 0}, {10, 10, 0, 1.0});


	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	

	//大きいマリオ
	sprite_->Draw();

	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
