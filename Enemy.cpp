#include "Enemy.h"
#include "MatrixTrans.h"
#include <cassert>


void Enemy::Initialize(Model* model, uint32_t textureHandle)
{ 
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	EnemytextureHandle_ = textureHandle;


	worldTransform_.Initialize();

}


void Enemy::Update()
{

	Vector3 move = {0, 0.01, -0.2f};
	

	// �����Z
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);


	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}


void Enemy::Draw(ViewProjection& viewProjection) 
{

	model_->Draw(worldTransform_, viewProjection, EnemytextureHandle_);

}
