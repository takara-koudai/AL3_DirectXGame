#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"
#include"AxisIndicator.h"
#include <cassert>
#include "Scene.h"

class ClearScene 
{
public:


	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	ClearScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ClearScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	//bool IsSceneEnd2() { return isSceneEnd2; }

	SceneType NextScene() { return SceneType::kTitle; }
	SceneType Nextscene2() { return SceneType::kEndeScene; }
	SceneType NextScene3() { return SceneType::kClearScene; }

	void Reset() { isSceneEnd = false; }
	//void Reset2() { isSceneEnd2 = false; }


private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// �f�o�b�O�J����
	DebugCamera* debugCamera_ = nullptr;

	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	// �^�C�g���̃e�N�X�`��
	uint32_t ClearTextureHandle = 0u;


	Sprite* clearSprite = nullptr;

	uint32_t start = 0;

	// �V�[���J��
	bool isSceneEnd = false;
	//bool isSceneEnd2 = false;

};
