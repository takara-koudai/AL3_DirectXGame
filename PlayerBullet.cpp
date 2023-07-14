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
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;

}

Vector3 PlayerBullet::GetWorldPosition() 
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;

	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void PlayerBullet::OnCollision()
{ 
	isDead_ = true;
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