#include "ClearScene.h"
#include "TextureManager.h"

ClearScene::ClearScene(){};

ClearScene::~ClearScene()
{
	delete clearSprite;
}

void ClearScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// �N���A
	ClearTextureHandle = TextureManager::Load("clear.png");

	clearSprite = Sprite::Create(ClearTextureHandle, {0, 0});

	// �f�o�b�N�J�����̐���
	debugCamera_ = new DebugCamera(1280, 720);

	// �������\���̕\����L���ɂ���
	AxisIndicator::GetInstance()->SetVisible(true);
	// �������\�����Q�Ƃ���r���[�v���W�F�N�V�������w�肷��(�A�h���X�n��)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

}

void ClearScene::Update()
{
	if (input_->TriggerKey(DIK_SPACE)) 
	{
		isSceneEnd = true;
	}

}

void ClearScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();


	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	///< summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	///</summary>
	

	clearSprite->Draw();
	
	
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();


	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	///< summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	///</summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();



	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	///< summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	///</summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();


	
}

