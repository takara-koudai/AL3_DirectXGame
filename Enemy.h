#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>

enum class Phase
{
	Approach,
	Leave,
};

class Enemy
{
public:


	//������
	void Initialize(Model* model, uint32_t textureHandle);



	//�X�V����
	void Update();



	//�`��
	void Draw(ViewProjection& viewProjection);


	// �e����
	void Fire(Vector3& position_);


	~Enemy();


	static const int kFireInterval = 60;
	

	//�ڋ߃t�F�[�Y�̏�����
	void Phase_();


private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// ���f��
	Model* model_ = nullptr;

	uint32_t EnemytextureHandle_ = 0u;
	

	//�t�F�[�Y
	Phase phase_ = phase_;

	// �e
	EnemyBullet* Enemybullet_ = nullptr;

	// �e
	std::list<EnemyBullet*> Enemybullets_;


	//���˃^�C�}�[
	int32_t fireTimer = 0;

};

