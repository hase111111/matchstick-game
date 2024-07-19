#include "ReplayScene.h"
#include "GameParam.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Define.h"

ReplayScene::ReplayScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
{
	//�p�����[�^��ǂݍ���
	m_loadParam(parameter);

	//�V�[���`�F���W�̃G�t�F�N�g��}������
	m_sceneChange.init(1);

	//�t�B�[���h���X�g���m�F���ĕs���ȃf�[�^���ǂ������ׂ�
	if (m_isIllegalFieldList(m_field_list) == true)
	{
		m_illegal_field = true;
		//printfDx("�s���ȃt�B�[���h�f�[�^�ł�\n");
	}
	//�s���łȂ��Ȃ�e�N���X��������
	else 
	{
		m_gameAnime.init(m_self_rule, m_mod_rule,true);	//�A�j���Ƀ��[����`����
		m_field = m_field_list.at(m_turn);			//�擪�̃t�B�[���h��`����

		//�A�j���[�V�������Z�b�g����
		if (m_field.turn == true) { m_gameAnime.addAnime(0); }
		else { m_gameAnime.addAnime(1); }

		//���O��ǉ�
		if (m_field.turn == true) { m_gameLog.pushLog("�M���͐��ł�"); }
		else { m_gameLog.pushLog("�M���͌��ł�"); }
		m_gameLog.pushLogByField(m_field_list.at(m_turn));
	}
}

bool ReplayScene::update()
{

	if (m_sceneChange.update() == false)
	{
		//�V�[���`�F���W�t���O�������Ă���Ȃ�΃V�[����߂�
		if (m_scene_change == true) 
		{
			Parameter p;
			mp_listenerInterface->deleteNowScene(p);
		}
		//�����Ă��Ȃ��Ȃ�Βʏ�̏������s��
		else 
		{
			//�ُ�ȃt�B�[���h���X�g��ǂݍ���ł���ꍇ�I������
			if (m_illegal_field == true) 
			{
				m_sceneChange.init(0);
				m_scene_change = true;
			}
			//�ُ�łȂ��Ȃ�Ε��ʂɏ���������
			else 
			{
				//ESCAPE�L�[�������ꂽ��V�[�����I��
				if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) 
				{
					m_sceneChange.init(0);
					m_scene_change = true;
				}
				else 
				{
					//�A�j���[�V�����I�����Ă��鎞�̂ݎ��s
					if (m_gameAnime.update() == false) 
					{
						//�t�B�[���h��S�ĕ\�����������Ȃ�ΏI���
						if (m_turn + 1 >= (int)m_field_list.size()) 
						{
							m_sceneChange.init(0);
							m_scene_change = true;
							return true;
						}
						else 
						{
							m_gameAnime.addAnime(4);
							m_gameAnime.addAnimeOption(m_field_list.at(m_turn), m_field_list.at((size_t)m_turn + 1));
							m_gameLog.pushLogByField(m_field_list.at((size_t)m_turn + 1));
							m_turn++;
						}
					}
					//�A�j���̍Đ����I������Ȃ�΃t�B�[���h������������
					else if (m_gameAnime.isEndTime() == true) 
					{
						if (m_turn < (int)m_field_list.size()) 
						{
							m_field = m_field_list.at(m_turn);
						}
					}
				}
			}
		}
	}

	return true;
}

void ReplayScene::draw() const
{
	//�w�i�͔����F
	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);

	//�r��`�悷��
	m_gameHand.draw(m_field, false, 0, 0, 0, false, false);

	//�ΐ탍�O��\������
	m_gameLog.draw(m_field, m_turn + 1, m_player_is_first, m_mod_rule, m_self_rule, 20000000);

	//�e��A�j���[�V��������ɕ\��
	m_gameAnime.draw();

	//�V�[���`�F���W�̃G�t�F�N�g��`��
	m_sceneChange.draw();
}

void ReplayScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
	//�V�[���`�F���W�̃G�t�F�N�g��}������
	m_sceneChange.init(1);
}

void ReplayScene::m_loadParam(const Parameter parameter)
{
	//�Q�[���N���X���烋�[�����󂯎��
	if (parameter.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_rule = true; }
	else { m_self_rule = false; }

	if (parameter.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
	else { m_mod_rule = false; }

	//�t�B�[���h���Q�[���N���X����󂯎��
	parameter.getFieldParam(m_field_list);
}

bool ReplayScene::m_isIllegalFieldList(const std::vector<MatchField>& _field) const
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
		for (auto& i : _field)
		{
			_map_checker[i]++;
		}

		//��ԑ����o�ꂵ���Ֆʂ̓o��񐔂��L�^����
		int _MAX_field_num = -1;

		for (auto& i : _map_checker)
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
		if (_field.back().doesWinFirstPlayer() == true && _field.back().doesWinSecondPlayer() == true)
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
