#include "ResultScene.h"
#include "DxLib.h"
#include "GameParam.h"
#include "Keyboard.h"
#include "Sound.h"

ResultScene::ResultScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli,parameter)
{
	//�Q�[���N���X���烋�[�����󂯎��
	if (parameter.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_rule = true; }
	else { m_self_rule = false; }

	if (parameter.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
	else { m_mod_rule = false; }
	m_drawKey.init(m_mod_rule, m_self_rule);

	m_scene_back_num = parameter.getParam(GameParam::RESULT_BACK_NUM);
	m_scene_back_num = (m_scene_back_num == 1 || m_scene_back_num == 2) ? m_scene_back_num : 1;
	if (m_scene_back_num == 1) { m_replay_save = true; }

	//�t�B�[���h���Q�[���N���X����󂯎��
	parameter.getFieldParam(m_field_list);

	//�t�B�[���h���X�g���m�F���ĕs���ȃf�[�^���ǂ������ׂ�
	clsDx();
	if (m_isIllegalFieldList(m_field_list) == true) 
	{
		m_illegal_field = true;
		printfDx("�s���ȃt�B�[���h�f�[�^�ł�\n"); 
	}

	//�����`��p�֐��Ƀf�[�^��������
	if (m_illegal_field == false) 
	{
		m_drawString.init(m_field_list, m_mod_rule, m_self_rule);
		m_drawString.update(0);

		m_drawHand.init(m_field_list);
		m_drawHand.update(0);
	}

	//�V�[���`�F���W�̃G�t�F�N�g��}������
	m_sceneChange.init(1);
}

bool ResultScene::update()
{
	if (m_sceneChange.update() == false)
	{
		//�s���ȃf�[�^�łȂ���Ώ������s��
		if (m_illegal_field == false)
		{
			//�V�[���`�F���W�̃t���O�������Ă���Ȃ�V�[����؂�ւ���
			if (m_scene_change == true)
			{
				Parameter p;
				mp_listenerInterface->deleteNowScene(p, m_scene_back_num);	//2�V�[���߂�
			}

			//ESC�L�[�������ꂽ�ꍇ�V�[���`�F���W������
			if (m_drawKey.update(m_field_list, m_select_field, m_replay_save, m_replay_fail) == false)
			{
				m_sceneChange.init(0);	//�V�[���`�F���W�̃G�t�F�N�g��}��
				m_scene_change = true;	//�V�[���`�F���W�̃t���O���I���ɂ���				
			}

			//�`��p�֐��Ɍ��ݑI�����Ă���ꏊ��������
			m_drawString.update(m_select_field);
			m_drawHand.update(m_select_field);
		}
		//�s���ȃf�[�^�������ꍇ�V�[�����I������
		else
		{
			if (m_scene_change == true)
			{
				//�V�[���`�F���W������
				Parameter p;
				mp_listenerInterface->deleteNowScene(p, m_scene_back_num);	//2�V�[������1�V�[���߂�
			}
			else
			{
				m_sceneChange.init(0);	//�V�[���`�F���W�̃G�t�F�N�g��}��
				m_scene_change = true;	//�V�[���`�F���W�̃t���O���I���ɂ���	
			}
		}
	}

	return true;
}

void ResultScene::draw() const
{
	//�w�i
	m_drawBack.draw();

	//�����\��
	m_drawString.draw(m_replay_save, m_replay_fail);

	//��̕\��
	m_drawHand.draw();

	//�V�[���`�F���W�G�t�F�N�g
	m_sceneChange.draw();
}

void ResultScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//�V�[���`�F���W�̃G�t�F�N�g��}������
	m_sceneChange.init(1);
}

//�t�B�[���h���X�g���s�����ǂ������ׂ�
bool ResultScene::m_isIllegalFieldList(const std::vector<MatchField>& _field) const
{
	//�t�B�[���h�̐��� 0 or 1 �Ȃ�s���Ƃ���
	if (_field.size() == 0 || _field.size() == 1) 
	{
		printfDx("�t�B�[���h����,���邢��1�݂̂ł�\n\n");
		return true; 
	}

	//�܂��͏��s�����Ă��邩�ǂ������ׂ�
	if (_field.back().isEndOfGame() == false) 
	{
		//���s�����Ă��Ȃ��ꍇ�����������ǂ������ׂ�
		std::map<MatchField, int> _map_checker;

		//�}�b�v�N���X��p���Ċe�Ֆʂ��o�ꂵ���񐔂��J�E���g����
		for (auto &i : _field)
		{
			_map_checker[i]++;
		}

		//��ԑ����o�ꂵ���Ֆʂ̓o��񐔂��L�^����
		int _MAX_field_num = -1;

		for (auto &i : _map_checker)
		{
			if (i.second > _MAX_field_num) { _MAX_field_num = i.second; }
		}

		//�����Ɣ��f�����񐔂�������Ă����ꍇ�s��
		if (_MAX_field_num < VariousFunctionsForMatchGame::SENNICHITE) 
		{
			printfDx("���������Ă��܂��񂪁A�����ł͂���܂���ł���\n");
			return true;
		}
	}
	else {
		//���������Ă���ꍇ���ҏ����ƂȂ��Ă��Ȃ����m���߂�
		if(_field.back().doesWinFirstPlayer() == true && _field.back().doesWinSecondPlayer() == true)
		{
			//���ҏ����ƂȂ�Ֆʂ͕s��
			printfDx("���ҏ�������ƂȂ�Ֆʂł�\n");
			return true;
		}
	}

	//���ɁA�Ֆʂ������������ŕ���ł��邩���ׂ�
	MatchField _next;
	int command = 0;

	for (size_t i = 0; i < _field.size(); i++)
	{
		//�Ֆʂ��Ō�̔ՖʂłȂ��ꍇ
		if (i < _field.size() - 1)
		{
			//���Ֆʂւ̃R�}���h���擾����
			command = VariousFunctionsForMatchGame::getCommand(_field.at(i), _field.at(i + 1), m_mod_rule, m_self_rule);

			//�R�}���h���s���Ȃ��̂����ׂ�
			if (command == VariousFunctionsForMatchGame::COMMAND_ERROR)
			{
				printfDx("�ՖʂɘA����������܂���%d\n", i);
				return true;
			}
		}
	}

	//�S�Ē��׏I������Ȃ�ӂ����łȂ�
	return false;
}


