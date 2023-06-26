#include "Enemy.h"
//#include "EnemyBullet.h"
#include "MatrixTrans.h"
#include <cassert>

Enemy::~Enemy()
{
	for (EnemyBullet* Enemybullet : Enemybullets_)
	{
		delete Enemybullet_;
	}
}

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	EnemytextureHandle_ = textureHandle;

	worldTransform_.Initialize();

	worldTransform_.translation_.z = 50.0f;
	worldTransform_.translation_.x = 30.0f;

	phase_ = Phase::Approach;

	Phase_();
}

void Enemy::Fire(Vector3& position_) 
{

	// �e�̑��x
	const float kBulletSpeed = -2.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// �e�𐶐����A������
	EnemyBullet* newEnemyBullet = new EnemyBullet();
	newEnemyBullet->Initialize(model_, position_, velocity);

	// �e��o�^����
    //Enemybullet_ = newEnemyBullet;
	

	Enemybullets_.push_back(newEnemyBullet);
}

// �ڋ߃t�F�[�Y�֐�
void Enemy::Phase_()
{
	// ���˃^�C�}�[��������
	fireTimer = kFireInterval;
}

void Enemy::Update()
{

	Vector3 move = {0.0, 0.0, 0.0f};

	const float kCharacterSpeed = 0.2f;

	switch (phase_) {
	case Phase::Approach: // �ڋ߃t�F�[�Y
	default:

		// �ړ�(�x�N�g���̉��Z)
		move.z -= kCharacterSpeed;
		
		//
		//Enemy��Update���Ă�
		

		// �G�̍U������
		// ���˃^�C�}�[�J�E���g�_�E��
		fireTimer--;
		

		// �w�莞�ԂɒB����
		if (fireTimer <= 0)
		{

			// �e�𔭎�
			Fire(worldTransform_.translation_);

			//Enemybullet_->Update();
			for (EnemyBullet* bullet : Enemybullets_) 
			{
				bullet->Update();
			}
			

			// ���˃^�C�}�[��������
			fireTimer = kFireInterval;

		}

		// �K��̈ʒu�ɓ��B�������E
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

	// �f�X�t���O���������e���폜
	Enemybullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}

		return false;
	});
	

	for (EnemyBullet* bullet : Enemybullets_) 
	{
		bullet->Update();
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

	// �e�̕`��
	for (EnemyBullet* Enemybullet : Enemybullets_)
	{
		Enemybullet->Draw(viewProjection);
	}

	if (Enemybullet_)
	{
		Enemybullet_->Draw(viewProjection);
	}

}
