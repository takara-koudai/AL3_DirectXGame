#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "Player.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "TitleScene.h"
#include "WinApp.h"
#include "EndScene.h"
#include "ClearScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	EndScene* endScene = nullptr;
	ClearScene* clearScene = nullptr;


	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"LE2C_18_タナカ_コウダイ_AL3");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	// タイトルシーン初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	//ゲームオーバー
 	endScene = new EndScene();
	endScene->Initialize();

	//クリア
	clearScene = new ClearScene();
	clearScene->Initialize();


	SceneType sceneNo = SceneType::kTitle;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		switch (sceneNo) {
		case SceneType::kTitle:

			// スペースが押されたらシーン移動
			titleScene->Update();

			if (titleScene->IsSceneEnd() == true) {

				sceneNo = titleScene->NextScene();
			    
				gameScene->Reset();
				endScene->Reset();
				clearScene->Reset();

			}

			break;
		case SceneType::kGameScene:

			// ゲームシーンの毎フレーム処理
			gameScene->Update();
			//titleScene->Reset();

			//clearScene->Update();

			// (gameSceneクラスのisSceneEnd変数が()の中に書かれてる)
			if (gameScene->IsSceneEnd() == true) 
			{
				sceneNo = gameScene->NextScene();// 次のシーンに行く処理
				//gameScene->Reset();
			}

			//クリア画面に飛ばす
			if (gameScene->ClearScene() == true)
			{
				sceneNo = gameScene->NextScene2();
				//gameScene->Reset();
			}


			break;
		case SceneType::kEndeScene:

			endScene->Update();

			if (endScene->IsSceneEnd() == true)
			{
				sceneNo = endScene->NextScene();

				titleScene->Reset();
				gameScene->Reset();
				endScene->Reset();
				//clearScene->Reset();

			}


			break;
		case SceneType::kClearScene:

			clearScene->Update();

			if (clearScene->IsSceneEnd() == true)
			{
				sceneNo = clearScene->NextScene();

				titleScene->Reset();
				gameScene->Reset();
				gameScene->ClearReset();
				endScene->Reset();
				clearScene->Reset();

			}


			break;
		}

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();

		switch (sceneNo) {
		case SceneType::kTitle:

			//タイトルの描画
			titleScene->Draw();

			break;
		case SceneType::kGameScene:

			// ゲームシーンの描画
			gameScene->Draw();

			break;
		case SceneType::kEndeScene:

			//ゲームオーバー画面
			endScene->Draw();


			break;
		case SceneType::kClearScene:

			//クリア
			clearScene->Draw();

			break;
		}

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}