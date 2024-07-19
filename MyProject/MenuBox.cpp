#include "MenuBox.h"
#include"DxLib.h"
#include"Define.h"
#include"Keyboard.h"
#include"Font.h"
#include"Sound.h"
#include"RuleParam.h"
#include"GameParam.h"
#include"Setting.h"

MenuBox::MenuBox() : 
	BOX_X(Define::WIN_SIZEX * 53 / 64), 
	BOX_Y(Define::WIN_SIZEY * 3 / 32)
{
	//�t�H���g�̃��[�h
	m_font_32 = myLoadFont("data/font/PixelMplus10_size32.dft");
	m_font_20 = myLoadFont("data/font/PixelMplus10_size20.dft");

	//�T�E���h�̃��[�h
	m_sound_select = Sound::getIns()->myLoadSound("data/sound/selecting.mp3");
	m_sound_select2 = Sound::getIns()->myLoadSound("data/sound/selecting2.mp3");
	m_sound_cancel = Sound::getIns()->myLoadSound("data/sound/cancel.mp3");

	//�ݒ�̃��[�h
	m_updateSetting();
}

bool MenuBox::update(enumScene& _scene, Parameter& _param)
{
	//�V�[���؂�ւ��̏���
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1 && (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) > 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RCONTROL) > 0)) 
	{
		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//�I������炷
		m_counter++;
		m_command_counter = 0;

		m_updateSetting();	//�ݒ��ǂݍ��݂Ȃ���
		m_resetReplayFile();//�t�@�C�����A�����[�h����
	}
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1 && (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) > 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RCONTROL) > 0)) 
	{
		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//�I������炷
		m_counter += m_MENU_NUM - 1;
		m_command_counter = 0;

		m_updateSetting();	//�ݒ��ǂݍ��݂Ȃ���
		m_resetReplayFile();//�t�@�C�����A�����[�h����
	}
	//���{�^�����������Ƃ�
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) 
	{
		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//�I������炷

		m_command_counter += 1;	//���ڂ�ύX

		//�ΐ�̉��Ɉړ�
		if (m_command_counter > 5) 
		{
			m_counter += 1;
			m_command_counter = 0;

			m_updateSetting();	//�ݒ��ǂݍ��݂Ȃ���
			m_resetReplayFile();//�t�@�C�����A�����[�h����
		}

		//���ڂ̐������Ȃ����v���C�̂��߂̏���
		if (m_counter % m_MENU_NUM == 2 && m_command_counter % 6 >= 4) 
		{
			m_counter += 1;
			m_command_counter = 0;

			m_updateSetting();	//�ݒ��ǂݍ��݂Ȃ���
			m_resetReplayFile();//�t�@�C�����A�����[�h����
		}
	}
	//��{�^�����������Ƃ�
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) 
	{
		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//�I������炷

		m_command_counter -= 1;	//���ڂ�ύX

		//�ΐ�̏�Ɉړ�
		if (m_command_counter < 0) 
		{
			m_counter += m_MENU_NUM - 1;
			m_command_counter = 5;

			m_updateSetting();	//�ݒ��ǂݍ��݂Ȃ���
			m_resetReplayFile();//�t�@�C�����A�����[�h����
		}

		//���ڂ̐������Ȃ����v���C�̂��߂̏���
		if (m_counter % m_MENU_NUM == 2 && m_command_counter % 6 >= 4)
		{
			m_command_counter = 3;
		}
	}

	//���E�L�[�ɂ�鏈��
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) 
	{
		//����vsCPU��I��
		if (m_counter % m_MENU_NUM == 0)
		{
			PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

			if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 1; }					//��s�v���C���[
			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 1; }				//CPU
			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai; }	//�єz
			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//����
			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5
		}
		//���ڃ��v���C��I��
		else if (m_counter % m_MENU_NUM == 2) 
		{
			if (m_command_counter % 4 == 1 && m_file_load_flag == true)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				m_file_select++;
			}
		}
		//���ڐݒ��I��
		else if (m_counter % m_MENU_NUM == 3)
		{
			//����
			if (m_command_counter % m_BATTLE_NUM == 2)
			{
				m_setting_vol += 5;
				m_setting_vol = (m_setting_vol > 100) ? 100 : m_setting_vol;

				//���ʂ����ݒ肵�čĐ�
				Sound::getIns()->changeVolume(m_setting_vol);
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
			}
			//�E�B���h�E���[�h
			else if (m_command_counter % m_BATTLE_NUM == 3)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);

				m_setting_win_ful = !m_setting_win_ful;
			}
			//�A�j�����J�b�g
			else if (m_command_counter % m_BATTLE_NUM == 4)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);

				m_setting_anime_cut = !m_setting_anime_cut;
			}
		}
	}
	else if(Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) 
	{
		//����vsCPU��I��
		if (m_counter % m_MENU_NUM == 0)
		{
			PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

			if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 2; }					//��s�v���C���[
			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 3; }				//CPU
			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai;  }	//�єz
			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//����
			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5
		}
		//���ڃ��v���C��I��
		else if (m_counter % m_MENU_NUM == 2)
		{
			if (m_command_counter % 4 == 1 && m_file_load_flag == true)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				m_file_select += (int)m_file_list.size() - 1;
			}
		}
		//���ڐݒ��I��
		else if (m_counter % m_MENU_NUM == 3)
		{
			//����
			if (m_command_counter % m_BATTLE_NUM == 2) 
			{
				m_setting_vol -= 5;
				m_setting_vol = (m_setting_vol < 0) ? 0 : m_setting_vol;

				//���ʂ����ݒ肵�čĐ�
				Sound::getIns()->changeVolume(m_setting_vol);
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
			}
			//�E�B���h�E���[�h
			else if (m_command_counter % m_BATTLE_NUM == 3)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);

				m_setting_win_ful = !m_setting_win_ful;
			}
			//�A�j�����J�b�g
			else if (m_command_counter % m_BATTLE_NUM == 4)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);

				m_setting_anime_cut = !m_setting_anime_cut;
			}
		}
	}

	//Esc�L�[�ɂ�鏈��
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) 
	{
		PlaySoundMem(m_sound_cancel, DX_PLAYTYPE_BACK);

		_scene = enumScene::title;
		_param.resetParam();
		return true;
	}

	//Z�L�[�ɂ�錈��
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
	{
		//vs CPU���ڂ̐퓬�J�n��I����
		if (m_counter % m_MENU_NUM == 0) 
		{
			if (m_command_counter % 6 == 0) 
			{
				//�V�[���̐ݒ�
				_scene = enumScene::game;

				//�p�����[�^�̐ݒ�
				_param.resetParam();

				//���̎Z�o
				if (m_battle_first % 3 == 1 || (m_battle_first % 3 == 0 && GetRand(1) == 0)) { _param.setParam(GameParam::PLAYER_IS_FIRST, GameParam::TRUE_STATE); }
				else { _param.setParam(GameParam::PLAYER_IS_FIRST, GameParam::FALSE_STATE); }

				//CPU���x��
				if (m_battle_cpu % 4 == 0) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_EASY); }
				else if (m_battle_cpu % 4 == 1) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_NORMAL); }
				else if (m_battle_cpu % 4 == 2) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_HARD); }
				else { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_IMPOSSIBLE); }

				//MOD���[���̐ݒ�
				if (m_battle_mod == true) { _param.setParam(GameParam::MOD_RULE, GameParam::TRUE_STATE); }
				else { _param.setParam(GameParam::MOD_RULE, GameParam::FALSE_STATE); }

				//�����̐ݒ�
				if (m_battle_self == true) { _param.setParam(GameParam::SELF_HARM_RULE, GameParam::TRUE_STATE); }
				else { _param.setParam(GameParam::SELF_HARM_RULE, GameParam::FALSE_STATE); }

				//�єz�̐ݒ�
				if (m_battle_saihai == true) { _param.setParam(GameParam::SAIHAI_RULE, GameParam::TRUE_STATE); }
				else { _param.setParam(GameParam::SAIHAI_RULE, GameParam::FALSE_STATE); }

				return true;
			}
			else if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 1; }					//��s�v���C���[
			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 1; }				//CPU
			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai; }	//�єz
			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//����
			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5

			//�I������炷}
			if (m_command_counter % m_BATTLE_NUM != 0) { PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK); }
		}
		//���[���m�F�̍��ڂ�I��
		else if (m_counter % m_MENU_NUM == 1) 
		{
			//�V�[���̐ݒ�
			_scene = enumScene::rule;

			//�p�����[�^�̐ݒ�
			_param.resetParam();
			if (m_command_counter % 6 == 0) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_BASIC); }
			else if (m_command_counter % 6 == 1) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SLEF); }
			else if (m_command_counter % 6 == 2) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SAIHAI); }
			else if (m_command_counter % 6 == 3) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_MOD_5); }
			else if (m_command_counter % 6 == 4) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SENRYAKU); }
			else if (m_command_counter % 6 == 5) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_OTHER); }

			return true;
		}
		//���v���C�̍��ڂ�I��
		else if (m_counter % m_MENU_NUM == 2)
		{
			//�ǂݍ���
			if (m_command_counter % 4 == 0 && m_file_load_flag == false) 
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				//�t���O�𗧂Ă�
				m_file_load_flag = true;

				//�ǂݍ���
				if (m_getReplayFileList() == false) {
					m_file_error_log = "�t�@�C����ǂݍ��߂܂���ł���";
				}
				else {
					m_file_error_log = "�ǂݍ��ݐ��� " + std::to_string(m_file_list.size()) + "�t�@�C��";
				}

			}
			//�t�@�C���I��
			else if (m_command_counter % 4 == 1 && m_file_load_flag == true) 
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				m_file_select++;
			}
			//�t�@�C������
			else if (m_command_counter % 4 == 2 && m_file_load_flag == true && m_file_list.size() != 0)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				//���v���C�t�@�C���̓ǂݍ���
				std::vector<MatchField> m_field_list_param;
				bool m_mod_rule_param = false;
				bool m_self_harm_param = false;
				std::string m_file_path_param = "./replay/" + m_file_list.at(m_file_select % m_file_list.size());

				if (VariousFunctionsForMatchGame::inputFieldList(m_file_path_param, m_field_list_param, m_mod_rule_param, m_self_harm_param) == false)
				{
					m_file_error_log = "���v���C�t�@�C���̓ǂݍ��݂Ɏ��s";
				}
				else 
				{
					//�ǂݍ��݂ɐ��������ꍇ�p�����[�^���Z�b�g���ēǂ݂���
					_scene = enumScene::result;

					_param.resetParam();
					_param.setFieldParam(m_field_list_param);
					_param.setParam(GameParam::MOD_RULE, (m_mod_rule_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
					_param.setParam(GameParam::SELF_HARM_RULE, (m_self_harm_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
					_param.setParam(GameParam::RESULT_BACK_NUM, 1);
					return true;
				}
			}
			//�t�@�C���Đ�
			else if (m_command_counter % 4 == 3 && m_file_load_flag == true && m_file_list.size() != 0)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//�I������炷

				//���v���C�t�@�C���̓ǂݍ���
				std::vector<MatchField> m_field_list_param;
				bool m_mod_rule_param = false;
				bool m_self_harm_param = false;
				std::string m_file_path_param = "./replay/" + m_file_list.at(m_file_select % m_file_list.size());

				if (VariousFunctionsForMatchGame::inputFieldList(m_file_path_param, m_field_list_param, m_mod_rule_param, m_self_harm_param) == false)
				{
					m_file_error_log = "���v���C�t�@�C���̓ǂݍ��݂Ɏ��s";
				}
				else
				{
					//�ǂݍ��݂ɐ��������ꍇ�p�����[�^���Z�b�g���ēǂ݂���
					_scene = enumScene::replay;

					_param.resetParam();
					_param.setFieldParam(m_field_list_param);
					_param.setParam(GameParam::MOD_RULE, (m_mod_rule_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
					_param.setParam(GameParam::SELF_HARM_RULE, (m_self_harm_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
					return true;
				}
			}
		}
		//�ݒ�̍��ڂ�I��
		else if (m_counter % m_MENU_NUM == 3) 
		{
			//�ݒ��ۑ�����
			if (m_command_counter % 6 == 0) 
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//���y���Đ�
				Setting::getIns()->saveSettingFile(m_setting_vol, m_setting_win_ful, m_setting_anime_cut);	//�ݒ��ۑ�����
				Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());	//���ʐݒ�
			}
			//�ݒ������������
			else if (m_command_counter % 6 == 1) 
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
				//�f�t�H�̐ݒ�ɖ߂�
				m_setting_vol = Setting::getIns()->getSettingVol(true);
				m_setting_win_ful = Setting::getIns()->getSettingFulWin(true);
				m_setting_anime_cut = Setting::getIns()->getSettingAnime(true);
			}
			//����
			else if (m_command_counter % 6 == 2)
			{
				m_setting_vol += 10;
				m_setting_vol = (m_setting_vol > 100) ? (m_setting_vol % 100) : m_setting_vol;

				//���ʂ����ݒ肵�čĐ�
				Sound::getIns()->changeVolume(m_setting_vol);
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
			}
			//�t���X�N���[��
			else if (m_command_counter % 6 == 3)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
				m_setting_win_ful = !m_setting_win_ful;
			}
			//�A�j��
			else if (m_command_counter % 6 == 4)
			{
				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
				m_setting_anime_cut = !m_setting_anime_cut;
			}
			//�Q�[���I����I������
			else if (m_command_counter % 6 == 5)
			{
				m_game_end_flag = true;
			}
		}
	}

	return false;
}

bool MenuBox::getGameEnd() const
{
	return m_game_end_flag;
}

void MenuBox::draw() const
{
	//�w�i�̎l�p��`�悷��
	m_drawBox();

	//����
	m_drawString();
}

//�����֌W�̊֐�
void MenuBox::m_updateSetting()
{
	//�ݒ�t�@�C���̃��[�h
	m_setting_vol = Setting::getIns()->getSettingVol();
	m_setting_win_ful = Setting::getIns()->getSettingFulWin();
	m_setting_anime_cut = Setting::getIns()->getSettingAnime();

	//�ݒ�t�@�C������̉��ʐݒ�
	Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());	
}

void MenuBox::m_resetReplayFile()
{
	//�t�@�C�����X�g����ɂ���
	m_file_list.clear();

	//�t���O���ւ��܂�
	m_file_load_flag = false;

	//�I�𒆂̃t�@�C����0��
	m_file_select = 0;

	//���O����ɂ���
	m_file_error_log = "";
}

bool MenuBox::m_getReplayFileList()
{
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;
	std::string search_name = "replay\\*.dat";

	hFind = FindFirstFile(search_name.c_str(), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}

	/* �w��̃f�B���N�g���ȉ��̃t�@�C�������t�@�C�����Ȃ��Ȃ�܂Ŏ擾���� */
	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			/* �f�B���N�g���̏ꍇ�͉������Ȃ� */
			printf("directory\n");
		}
		else {
			/* �t�@�C��������������Vector�z��ɕۑ����� */
			m_file_list.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return true;
}

//�`��֌W�̊֐�
void MenuBox::m_drawString() const
{
	//����
	m_drawString_VS();

	//���[��
	m_drawString_Rule();

	//���v���C
	m_drawString_Replay();

	//�ݒ�
	m_drawString_String();
}

void MenuBox::m_drawString_VS() const
{
	const int POSX = Define::WIN_SIZEX / 10;
	const int HALF_X = Define::WIN_SIZEX / 2;
	const int LEFT_MIDDLE = Define::WIN_SIZEX * 26 / 64;
	const int RIGHT_MIDDLE = Define::WIN_SIZEX * 38 / 64;
	std::string str;

	//���x�� VS CPU
	DrawStringToHandle(POSX, Define::WIN_SIZEY * 3 / 40, "vsCPU", GetColor(0xe5, 0xe5, 0xe5), m_font_32);

	//�I�� �I�����̕\��
	if (m_counter % m_MENU_NUM == 0)
	{
		//Z�L�[�ŏ����J�n
		str = "Z�L�[�ŏ����J�n";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 11 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		//�Œ肳��镶����\������
		{
			for (int i = 0; i < 5; i++)
			{
				// ������ :
				str = ":";
				DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * (15 + 4 * i) / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

				// �E�� < >
				str = "<            >";
				DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * (15 + 4 * i) / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
			}

			//�����̕���
			str = "��s�v���C���[";
			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 15 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			str = "CPU �̃��x��";
			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			str = "�єz���[��";
			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			str = "�������[��";
			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			str = "MOD 5 ���[��";
			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
		}

		//�I���ɂ���ĕύX����镶��
		{
			//��s�v���C���[
			if (m_battle_first % 3 == 0) { str = "�����_��"; }
			else if (m_battle_first % 3 == 1) { str = "���Ȃ�"; }
			else { str = "�G"; }
			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 15 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			//CPU�̃��x��
			if (m_battle_cpu % 4 == 0) { str = "EASY"; }
			else if (m_battle_cpu % 4 == 1) { str = "NORMAL"; }
			else if (m_battle_cpu % 4 == 2) { str = "HARD"; }
			else { str = "IMPOSSIBLE"; }
			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

			//�єz���[��
			if (m_battle_saihai == true) { str = "ON"; }
			else { str = "OFF"; }
			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), (m_battle_saihai == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);

			//�������[��
			if (m_battle_self == true) { str = "ON"; }
			else { str = "OFF"; }
			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), (m_battle_self == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);

			//MOD 5���[��
			if (m_battle_mod == true) { str = "ON"; }
			else { str = "OFF"; }
			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), (m_battle_mod == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);
		}
	}
}

void MenuBox::m_drawString_Rule() const
{
	const int POSX = Define::WIN_SIZEX / 10;
	const int HALF_X = Define::WIN_SIZEX / 2;
	std::string str;

	if (m_counter % m_MENU_NUM == 0) {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 24 / 40, "���[���m�F", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}
	else {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 8 / 40, "���[���m�F", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}

	if (m_counter % m_MENU_NUM == 1) {
		str = "��{���[��";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���[�J�����[�� : �@�@�єz�@�@ ";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���[�J�����[�� : �@�@�����@�@ ";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���[�J�����[�� : �@�@MOD 5�@�@";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�헪�w��";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���̃Q�[���ō̗p����Ă��Ȃ����[���ƕ⑫";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
	}
}

void MenuBox::m_drawString_Replay() const
{
	const int POSX = Define::WIN_SIZEX / 10;
	const int HALF_X = Define::WIN_SIZEX / 2;
	std::string str;
	int color = 0;

	if (m_counter % m_MENU_NUM == 0 || m_counter % m_MENU_NUM == 1) {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 29 / 40, "���v���C", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}
	else {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 13 / 40, "���v���C", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}

	if (m_counter % m_MENU_NUM == 2) 
	{
		//���[�h�̍���
		if (m_file_load_flag == false)
		{ 
			color = GetColor(0xff, 0, 0);
			str = "���v���C�t�@�C�������[�h����";
		}
		else 
		{
			color = GetColor(0x51, 0x51, 0x51);
			str = "���v���C�t�@�C���̃��[�h�ɐ������܂���"; 
		}
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), color, m_font_20);

		//���v���C�t�@�C����I�����鍀��
		if (m_file_load_flag == false) 
		{ 
			color = GetColor(0x51, 0x51, 0x51);
			str = "���v���C�t�@�C�������[�h���Ă�������";
		}
		else if(m_file_list.size() <= 0)
		{ 
			color = GetColor(0x11, 0x11, 0x11);
			str = "���v���C�t�@�C�������݂��܂���";
		}
		else {
			color = GetColor(0x11, 0x11, 0x11);
			str = "<�@";
			str += m_file_list.at(m_file_select % m_file_list.size());
			str += "�@>";
		}
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), color, m_font_20);

		//�ꂴ��Ƃ�\�����鍀��
		str = "���v���C�𕪐͂���";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���v���C���Đ�����";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�t�@�C���ǂݍ��݂̃��O";
		str += (m_file_error_log.size() == 0) ? "" : ":" + m_file_error_log;
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 45 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		/*
		* 		str = "�헪�w��";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "���̃Q�[���ō̗p����Ă��Ȃ����[���ƕ⑫";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
		*/
	}
}

void MenuBox::m_drawString_String() const
{
	const int POSX = Define::WIN_SIZEX / 10;
	const int HALF_X = Define::WIN_SIZEX / 2;
	const int QUARTER_X = (HALF_X + BOX_X / 2) / 2;
	std::string str;

	if (m_counter % m_MENU_NUM == 3) {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 18 / 40, "�e��ݒ�", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}
	else {
		DrawStringToHandle(POSX, Define::WIN_SIZEY * 34 / 40, "�e��ݒ�", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
	}

	if (m_counter % m_MENU_NUM == 3) 
	{
		str = "�ݒ��ۑ��E�K�p����";
		int color_code = GetColor(0x11, 0x11, 0x11);
		//����̃f�[�^�ƈႤ�Ȃ�F��Ԃ�
		if (m_setting_vol != Setting::getIns()->getSettingVol() || m_setting_win_ful != Setting::getIns()->getSettingFulWin() || m_setting_anime_cut != Setting::getIns()->getSettingAnime()) { color_code = GetColor(0xc0, 0x0, 0x0); }
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), color_code, m_font_20);

		str = "�ݒ������������";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�@�@�@�@�{�����[���ݒ�@�@�@�@";
		str += ": ���@�@�@�@�@�@�@�@�@�@�@�@�� ";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
		str = std::to_string(m_setting_vol) + "%";
		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�t���X�N���[���i�ċN���œK�p�j";
		str += ": ���@�@�@�@�@�@�@�@�@�@�@�@�� ";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
		str = (m_setting_win_ful) ? "�t���X�N���[���ŋN��" : "�E�B���h�E���[�h�ŋN��";
		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�@�퓬���̃A�j�����J�b�g����@";
		str += ": ���@�@�@�@�@�@�@�@�@�@�@�@�� ";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 51 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
		str = (m_setting_anime_cut) ? "�A�j�����J�b�g����" : "�J�b�g���Ȃ�";
		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 51 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);

		str = "�Q�[�����I������";
		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 55 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
	}
}

void MenuBox::m_drawBox() const
{
	const int HALFX = Define::WIN_SIZEX / 2;
	const int MINI_BOX_X = BOX_X;
	const int MINI_BOX_Y = (int)(BOX_Y / 1.6);

	//����
	if (m_counter % m_MENU_NUM == 0) {
		//�I��
		int POS1_Y = Define::WIN_SIZEY * 4 / 40;
		int POS2_Y = Define::WIN_SIZEY * 20 / 40;
		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS1_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);

		//�_�ł��锒����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
		int _miny = Define::WIN_SIZEY * 12 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	else {
		int POS1_Y = Define::WIN_SIZEY * 4 / 40;
		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS1_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}

	//���[��
	if (m_counter % m_MENU_NUM == 0) {
		int POS2_Y = Define::WIN_SIZEY * 25 / 40;
		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}
	else if (m_counter % m_MENU_NUM == 1) {
		//�I��
		const int POS2_Y = Define::WIN_SIZEY * 9 / 40;
		const int POS3_Y = Define::WIN_SIZEY * 25 / 40;
		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);

		//�_�ł��锒����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
		int _miny = Define::WIN_SIZEY * 20 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	else {
		const int POS2_Y = Define::WIN_SIZEY * 9 / 40;
		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}


	//���v���C
	if (m_counter % m_MENU_NUM == 3) 
	{
		const int POS3_Y = Define::WIN_SIZEY * 14 / 40;
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}
	else if (m_counter % m_MENU_NUM == 2) 
	{
		//�I��
		const int POS3_Y = Define::WIN_SIZEY * 14 / 40;
		const int POS4_Y = Define::WIN_SIZEY * 30 / 40;
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);

		//�_�ł��锒����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
		int _miny = Define::WIN_SIZEY * 28 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	else {
		const int POS3_Y = Define::WIN_SIZEY * 30 / 40;
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}


	//�ݒ�
	if (m_counter % m_MENU_NUM == 3) 
	{
		//�I��
		const int POS3_Y = Define::WIN_SIZEY * 19 / 40;
		const int POS4_Y = Define::WIN_SIZEY * 35 / 40;
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);

		//�_�ł��锒����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
		int _miny = Define::WIN_SIZEY * 36 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	}
	else {
		const int POS4_Y = Define::WIN_SIZEY * 35 / 40;
		DrawBox(HALFX - BOX_X / 2, POS4_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
	}
}
