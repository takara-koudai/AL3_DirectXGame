#include "Player.h"
#include <cassert>


//
//������
void Player::Initialize(Model* model, uint32_t textureHandle) { 

	//NULL�|�C���^�`�F�b�N
	assert(model);


	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

}

//
//�X�V����
void Player::Update()
{

	worldTransform_.TransferMatrix();

}



//
//�`��
void Player::Draw(ViewProjection &viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}