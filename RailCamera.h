#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"ImGuiManager.h"

class RailCamera
{
public:

	//<summary>
	// 初期化
	//</summary>

	void Initialize(Vector3 position, Vector3& radian);

	//<summary>
	// 更新
	//</summary>

	void Update();

	//<summary>
	// 描画
	//</summary>

	//void Draw();

	ViewProjection GetViewProjection() { return viewProjection_; }
	
	const WorldTransform &GetWorldTransform() const { return worldTransform_; }


private:


	// ワールド変換データ
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;


};
