#include "PlayerBullet.h"
#include <cassert>
#include "MatrixTrans.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) 
{

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	ModeltextureHandle_ = TextureManager::Load("black.png");

	//���[���h�g�����X�t�H�[��������
	//worldTransform_.translation_ = {};

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;

}


void PlayerBullet::Update() 
{

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	
	worldTransform_.UpdateMatrix(); 

	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}

}


void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{
	 model_->Draw(worldTransform_, viewProjection, ModeltextureHandle_);
}