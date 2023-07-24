#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome
{

public:

	//<summary>
	//初期化
	//</summary>


	//void Initialize(Model* model,uint32_t textureHandle);

	void Initialize(Model* model);


	//<summary>
	// 更新
	//</summary>


	void Update();


	//<summary>
	// 描画
	//</summary>


	void Draw(ViewProjection& viewProjection_);

private:

	//ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


	//モデル
	Model* model_ = nullptr;


	//uint32_t backGround_ = 0u;

};
