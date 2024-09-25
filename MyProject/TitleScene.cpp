#include "DxLib.h"
#include "TitleScene.h"
#include "Keyboard.h"
#include "Define.h"
#include "Font.h"
#include "Sound.h"
#include "GameParam.h"

TitleScene::TitleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : 
	AbstractScene(pScli, parameter),
	m_scene_change(false),
	m_sound(Sound::getIns()->myLoadSound("data/sound/op.mp3"))
{
	m_change.init(-1);
}

bool TitleScene::update()
{
	m_anime.update();

	if (m_change.update() == false) {

		if (m_scene_change == true) {
			//�V�[���`�F���W�̃G�t�F�N�g���I�������i�K�ŃV�[����ύX����
			Parameter _p;
			mp_listenerInterface->addNewScene(enumScene::menu, _p);
		}

		//Z�L�[�������ꂽ��V�[���؂�ւ�
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
		{
			m_scene_change = true;	//�V�[���ύX�t���O�𗧂Ă�
			m_change.init(2);		//�V�[���`�F���W�G�t�F�N�g���Đ�
			PlaySoundMem(m_sound, DX_PLAYTYPE_BACK);	//�T�E���h���Đ�
		}

		//ESC�L�[�������ꂽ��Q�[���I��
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1)
		{
			return false;
		}
	}

	return true;
}

void TitleScene::draw() const
{
	//�w�i
	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);

	//�R�s�[���C�g���w�i�̃A�j���[�V����
	m_anime.draw();

	//�V�[���`�F���W�̃G�t�F�N�g
	m_change.draw();
}

void TitleScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//�V�[���`�F���W�p�̃N���X�ƃt���O�����Z�b�g����
	m_scene_change = false;
	m_change.init(3);
}
