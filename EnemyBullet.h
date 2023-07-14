#pragma once
#include "Model.h"
#include "WorldTransform.h"


class EnemyBullet
{
public:

	//������
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);


	//�X�V����
	void Update();


	//�`��
	void Draw(const ViewProjection& viewProjection);


	bool IsDead() const { return isDead_; }


	// ���[���h���W���擾
	Vector3 GetWorldPosition();


	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();


private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// ���f��
	Model* model_ = nullptr;


	//�e�N�X�`���n���h��
	uint32_t EnemyBulletHandle_ = 0u;

	// �e�̑��x
	Vector3 velocity_;


	// ����<frm>
	static const int32_t kLifeTime = 60 * 5;

	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	// �f�X�t���O
	bool isDead_ = false;

	
	
};