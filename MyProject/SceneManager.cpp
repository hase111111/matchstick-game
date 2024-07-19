#include"SceneManager.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"MenuScene.h"
#include"ResultScene.h"
#include"RuleScene.h"
#include"DebugScene.h"
#include"ReplayScene.h"
#include"Error.h"

const int ADD_SCENE = 1;
const int BACK_SCENE = 2;
const int DELETE_ALL_SCENE = 3;
const int NO_COMMAND = -1;

SceneManger::SceneManger() : 
	m_first_scene(enumScene::title),
	m_scenechange_command(NO_COMMAND),
	m_scene_name(enumScene::title),
	m_how_many_scene(0)
{
	//��ԍŏ��̃V�[����ǉ�
	Parameter p;
	m_addNewScene(m_first_scene, p);
}

bool SceneManger::updateTopScene()
{
	if (m_uniqueSceneStack.empty() == true) {
		ERR("�V�[�������݂��Ă��Ȃ����߁A��ԏ�̃V�[�����X�V�ł��܂���");
	}

	//�g�b�v�̃V�[�����X�V����Bfalse���Ԃ��Ă�����\�t�g���I������
	return m_uniqueSceneStack.top()->update();
}

void SceneManger::drawTopScene() const
{
	if (m_uniqueSceneStack.empty() == true) {
		ERR("�V�[�������݂��Ă��Ȃ����߁A��ԏ�̃V�[����`��ł��܂���");
	}

	m_uniqueSceneStack.top()->draw();
}


void SceneManger::addNewScene(const enumScene _sceneName, const Parameter& parameter)
{
	//�V�[���ǉ��̖��߂��o��
	m_scenechange_command = ADD_SCENE;
	m_scene_name = _sceneName;
	m_tempParam = parameter;
}

void SceneManger::deleteNowScene(const Parameter& parameter,int _how_many)
{
	//�V�[���폜�̖��߂��o��
	m_scenechange_command = BACK_SCENE;
	m_tempParam = parameter;
	m_how_many_scene = _how_many;
}

void SceneManger::deleteAllScene()
{
	//�V�[���폜�̖��߂��o��
	m_scenechange_command = DELETE_ALL_SCENE;
}


void SceneManger::sceneChangeExecute()
{
	if (m_scenechange_command == NO_COMMAND) {
		//�������Ȃ�
	}
	else if (m_scenechange_command == ADD_SCENE) //�V�[���ǉ����߂̎�
	{
		//�V�[���ǉ�
		m_addNewScene(m_scene_name, m_tempParam);

		//���߂����Z�b�g����
		m_scenechange_command = NO_COMMAND;
		m_tempParam.resetParam();
	}
	else if (m_scenechange_command == BACK_SCENE) //�V�[���폜���߂̎�
	{
		//�V�[�����폜
		int cnt = (m_how_many_scene > 1) ? m_how_many_scene : 1;

		for (int i = 0; i < cnt; i++)
		{
			if (m_uniqueSceneStack.empty() == false) {
				m_uniqueSceneStack.pop();
			}
		}

		//�V�[�������݂��Ȃ��Ȃ�ŏ��̃V�[����ǉ�
		if (m_uniqueSceneStack.empty() == true) {
			Parameter p;
			m_addNewScene(m_first_scene, p);
		}

		//�V���ȃg�b�v�V�[���Ƀp�����[�^��n��
		if (m_uniqueSceneStack.empty() == true) { ERR("�V�[���폜�Ɏ��s���܂����B�V�[���������Ȃ��Ƃ���Ƀp�����[�^��}�����悤�Ƃ��Ă��܂�"); }
		m_uniqueSceneStack.top()->receiveParameterInCaseOfDeleteScene(m_tempParam);

		//���߂����Z�b�g����
		m_scenechange_command = NO_COMMAND;

		//�p�����[�^�����Z�b�g����
		m_tempParam.resetParam();
	}
	else if (m_scenechange_command == DELETE_ALL_SCENE) {
		//�S�V�[���폜���߂̎�

		//�S�V�[�����폜
		while (m_uniqueSceneStack.empty() == false) {
			m_uniqueSceneStack.pop();
		}

		//�ŏ��̃V�[����ǉ�
		Parameter p;
		m_addNewScene(m_first_scene, p);

		//���߂����Z�b�g����
		m_scenechange_command = NO_COMMAND;
		m_tempParam.resetParam();
	}
	else {
		std::string err = "�V�[���ύX�N���X�ŃG���[���������܂����B\n�s���ȃR�}���h...";
		err += std::to_string(m_scenechange_command);
		ERR(err);
	}

}

void SceneManger::m_addNewScene(const enumScene _scene_name, const Parameter& _parameter)
{
	switch (_scene_name)
	{
	case enumScene::title:
		m_uniqueSceneStack.push(std::make_unique<TitleScene>(this, _parameter));
		break;

	case enumScene::game:
		m_uniqueSceneStack.push(std::make_unique<GameScene>(this, _parameter));
		break;

	case enumScene::menu:
		m_uniqueSceneStack.push(std::make_unique<MenuScene>(this, _parameter));
		break;

	case enumScene::result:
		m_uniqueSceneStack.push(std::make_unique<ResultScene>(this, _parameter));
		break;

	case enumScene::rule:
		m_uniqueSceneStack.push(std::make_unique<RuleScene>(this, _parameter));
		break;

	case enumScene::debug:
		m_uniqueSceneStack.push(std::make_unique<DebugScene>(this, _parameter));
		break;

	case enumScene::replay:
		m_uniqueSceneStack.push(std::make_unique<ReplayScene>(this, _parameter));
		break;

	default:
		ERR("���݂��Ă��Ȃ��V�[���̒ǉ��˗����o����܂���");
		break;
	}
}
