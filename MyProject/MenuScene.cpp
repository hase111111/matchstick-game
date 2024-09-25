#include "MenuScene.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Error.h"

MenuScene::MenuScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
{
	m_scene_change_effect.init(3);
}

bool MenuScene::update()
{
	//�w�i�̍X�V�͏�ɍs��
	m_draw_back.update();

	//�V�[���G�t�F�N�g�̍X�V���I�����Ă��烁�C���̏������s��
	if (m_scene_change_effect.update() == false)
	{
		//�Q�[���I���̏���
		if (m_box.getGameEnd() == true) 
		{
			//�Q�[���I���Ȃ��FALSE��Ԃ�
			return false;
		}

		//�V�[���`�F���W���߂��o�邩�ǂ���
		if (m_box.update(m_which_scene, m_param) == true) {
			m_scene_change_flag = true;

			if (m_which_scene == enumScene::title) { m_scene_change_effect.init(2); }
			else { m_scene_change_effect.init(0); }

			return true;
		}

		//�V�[���`�F���W���߂��o�Ă���Ȃ��
		if (m_scene_change_flag == true) 
		{
			if (m_which_scene == enumScene::title) {
				mp_listenerInterface->deleteNowScene(m_param);
			}
			else if (m_which_scene == enumScene::game) {
				mp_listenerInterface->addNewScene(enumScene::game, m_param);
			}
			else if (m_which_scene == enumScene::rule) {
				mp_listenerInterface->addNewScene(enumScene::rule, m_param);
			}
			else if (m_which_scene == enumScene::result) {
				mp_listenerInterface->addNewScene(enumScene::result, m_param);
			}
			else if (m_which_scene == enumScene::replay) {
				mp_listenerInterface->addNewScene(enumScene::replay, m_param);
			}
			else { ERR("MenuScene����\�����Ȃ��V�[���ւ̈ړ��������s���܂����B\n�댯�ł͂Ȃ��ł����ʓ|�ȓ��삵�Ăق����Ȃ��̂ŏI�������܂���w"); }
			return true;
		}
	}

	return true;
}

void MenuScene::draw() const
{
	//�w�i��`��
	m_draw_back.draw();

	//�l�p��`��
	m_box.draw();

	//�V�[���`�F���W�G�t�F�N�g��`��
	m_scene_change_effect.draw();
}

void MenuScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//�V�[���`�F���W�̃G�t�F�N�g���Đ�����
	m_scene_change_effect.init(1);

	//�V�[���`�F���W�p�̃t���O��߂�
	m_scene_change_flag = false;
	m_which_scene = enumScene::title;
	m_param.resetParam();
}