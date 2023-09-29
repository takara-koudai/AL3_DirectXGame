#include "TitleScene.h"
#include "TextureManager.h"


TitleScene::TitleScene(){};

//デストラクタ
TitleScene::~TitleScene(){

	delete titleSprite;

};


//初期化
void TitleScene::Initialize() 
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	

	//タイトル
	TitleTextureHandle = TextureManager::Load("opening.png");  
	

	//タイトル描画
	titleSprite = Sprite::Create(TitleTextureHandle, {0, 0});


	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

}

//更新処理
void TitleScene::Update() 
{ 

	if (input_->TriggerKey(DIK_SPACE))
	{
		isSceneEnd = true;

	
	}

}

//描画
void TitleScene::Draw()
{
	//コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	//背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	///<summary>
	///ここに背景スプライトの描画処理を追加できる
	///</summary>
	

	titleSprite->Draw();



	//スプライト描画後処理
	Sprite::PostDraw();
	//深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	//3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	///< summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///</summary>
	 


	//3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	//前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	///< summary>
	/// ここに前景スプライトの描画処理を追加できる
	///</summary>

	//スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion

}






