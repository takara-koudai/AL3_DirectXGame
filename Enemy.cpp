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

	worldTransform_.translation_.z = 30.0f;

	phase_ = Phase::Approach;


}


void Enemy::Update()
{

	Vector3 move = {0.0, 0.0, 0.0f};

	const float kCharacterSpeed = 0.2f;


	switch (phase_) 
	{
	case Phase::Approach: // �ڋ߃t�F�[�Y
	default:

		// �ړ�(�x�N�g���̉��Z)

		move.z -= kCharacterSpeed;

		//�K��̈ʒu�ɓ��B�������E
		if (worldTransform_.translation_.z < 0.0f)
		{
			phase_ = Phase::Leave;
		}

		break;


	case Phase::Leave: // ���E�t�F�[�Y

		// �ړ�(�x�N�g���̉��Z)
		
		move.x -= kCharacterSpeed;
		move.y += kCharacterSpeed;
		move.z -= kCharacterSpeed;

		break;
	}


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
