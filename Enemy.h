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

//���@�N���X�̑O���錾
class Player;


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


	//�f�X�g���N�^
	~Enemy();


	//�e���ˊԊu
	static const int kFireInterval = 50;
	

	//�ڋ߃t�F�[�Y�̏�����
	void Phase_();


	//setter�̗��p
	void SetPlayer(Player* player) { player_ = player; }


	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	// �e���X�g
	const std::list<EnemyBullet*>& GetBullet() const { return Enemybullets_; }
	

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


	//���L����
	Player* player_ = nullptr;

	

};

