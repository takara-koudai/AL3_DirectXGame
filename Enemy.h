#pragma once
#include "Model.h"
#include "WorldTransform.h"

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


	
private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	// ���f��
	Model* model_ = nullptr;

	uint32_t EnemytextureHandle_ = 0u;


	//�t�F�[�Y
	Phase phase_ = phase_;

};

