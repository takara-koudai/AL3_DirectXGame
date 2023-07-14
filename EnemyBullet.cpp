#include "EnemyBullet.h"
#include <cassert>
#include "MatrixTrans.h"


void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;


	//�e�N�X�`���ǂݍ���
	EnemyBulletHandle_ = TextureManager::Load("RED.png");


	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocity_ = velocity;

}


void EnemyBullet::OnCollision()
{ 
	isDead_ = true;
}


Vector3 EnemyBullet::GetWorldPosition() 
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;

	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void EnemyBullet::Update()
{

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) 
	{
		isDead_ = true;
	}

}



void EnemyBullet::Draw(const ViewProjection& viewProjection)
{

	model_->Draw(worldTransform_, viewProjection, EnemyBulletHandle_);

}