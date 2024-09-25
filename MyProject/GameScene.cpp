#include "GameScene.h"
#include "DxLib.h"
#include "Define.h"
#include "Image.h"
#include "Keyboard.h"
#include "Font.h"
#include "GameParam.h"
#include "Sound.h"

GameScene::GameScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
{
	//�V�[���`�F���W���̃G�t�F�N�g�i�t�F�[�h�C���j��}������
	m_sceneChange.init(1);

	//�Ֆʂ��p�����[�^�����ɏ���������
	m_initField(parameter);

	//�Q�[���J�n�̃A�j���[�V������}������
	if (m_field.turn == true) { m_anime.addAnime(0); }
	else { m_anime.addAnime(1); }

	//Log�Ɍ��݂̔Ֆʂ�ǉ�����
	m_logDraw.pushLogByField(m_field);

	//�A�j���[�^�[�Ƀ��[����`����
	m_anime.init(m_self_harm_rule, m_mod_rule);

	//�T�E���h�̓ǂݍ���
	m_sound_hand_select = Sound::getIns()->myLoadSound("data/sound/hand_select.mp3");
	m_sound_hand_cancel = Sound::getIns()->myLoadSound("data/sound/hand_cancel.mp3");
}

bool GameScene::update()
{
	//ESC�������ꂽ��O�̃V�[���ɖ߂�
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1 && m_changescene_flag == false) 
	{
		m_changescene_flag = true;
		m_sceneChange.init(0);
		m_changescene_which = 1;
	}

	//�I�𒆂��ǂ����̃t���O�͊�{�I�t
	m_is_selecting_now = false;

	//�V�[���`�F���W�̃G�t�F�N�g���I������Ȃ烁�C���̏���������
	if (m_sceneChange.update() == false)
	{
		//�V�[���`�F���W�Ȃ炱����s��
		if (m_changescene_flag == true)
		{
			Parameter p;
			if (m_changescene_which == 1)
			{
				mp_listenerInterface->deleteNowScene(p);
			}
			else if (m_changescene_which == 2)
			{
				Parameter p;

				//�Q�[���̔Ֆʂ�񍐂���
				std::vector<MatchField> _temp_field_list;
				m_logDraw.getFieldList(_temp_field_list);
				p.setFieldParam(_temp_field_list);

				//�Q�[���̃��[����񍐂���
				if (m_self_harm_rule == true) { p.setParam(GameParam::SELF_HARM_RULE, GameParam::TRUE_STATE); }
				else { p.setParam(GameParam::SELF_HARM_RULE, GameParam::FALSE_STATE); }

				if (m_mod_rule == true) { p.setParam(GameParam::MOD_RULE, GameParam::TRUE_STATE); }
				else { p.setParam(GameParam::MOD_RULE, GameParam::FALSE_STATE); }

				//�ꂴ��ƃV�[�������V�[�����߂�̂�
				p.setParam(GameParam::RESULT_BACK_NUM, 2);

				//�V�[����ǉ�����
				mp_listenerInterface->addNewScene(enumScene::result, p);
			}

			return true;
		}

		//�A�j���[�V�����̏������I������Ȃ烁�C���̏���������
		if (m_anime.update() == false)
		{
			//�Q�[�����I�����Ă���Ȃ�A�j���[�V�������Đ�����
			if (m_field.isEndOfGame() == true)
			{
				m_changescene_flag = true;
				m_sceneChange.init(0);
				m_changescene_which = 2;
			}
			//���������̎��A�j���[�V�������Đ�����
			else if (m_logDraw.update() == false) 
			{
				m_changescene_flag = true;
				m_sceneChange.init(0);
				m_changescene_which = 2;
			}
			//�����̃^�[���̎�
			else if (m_field.turn == true)
			{
				//m_selectEnenmy();
				m_is_selecting_now = true;
				m_selectMove();
			}
			//�G�̃^�[���̎�
			else
			{
				m_selectEnenmy();
			}
		}
		//�A�j���[�V�������I�������^�C�~���O�Ńt�B�[���h�̍X�V��������
		else if (m_anime.isEndTime() == true) {
			m_pushNewFieldExecute();
		}
	}

	return true;
}

void GameScene::draw() const
{
	//�w�i�͔����F
	DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);

	//�r��`�悷��
	m_handDraw.draw(m_field, m_is_selecting_now, m_which_player, m_which_one_player1, m_which_one_player2, m_use_self_hurm, m_use_saihai);

	//�ΐ탍�O��\������
	m_logDraw.draw(m_field, m_turn, m_player_is_first, m_mod_rule, m_self_harm_rule, m_enemy_level);

	//�e��A�j���[�V��������ɕ\��
	m_anime.draw();

	//�V�[���`�F���W���̃G�t�F�N�g����ԏ�ɕ\��
	m_sceneChange.draw();
}

void GameScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
}


void GameScene::m_initField(const Parameter& _pram)
{
	//�ǂ����̃^�[�������ׂ�
	if (_pram.getParam(GameParam::PLAYER_IS_FIRST) == GameParam::TRUE_STATE) {
		m_logDraw.pushLog("�M���͐��ł�");
		m_field.turn = m_player_is_first = true;
	}
	else {
		m_logDraw.pushLog("�M���͌��ł�");
		m_field.turn = m_player_is_first = false;
	}

	//CPU
	if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_EASY) { m_enemy_level = 0; }
	else if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_NORMAL) { m_enemy_level = 1; }
	else if (_pram.getParam(GameParam::ENEMY_LEVEL) == GameParam::ENEMY_LEVEL_HARD) { m_enemy_level = 2; }
	else { m_enemy_level = 3; }

	//MOD���[�����g�p���邩�ǂ����̃t���O
	if (_pram.getParam(GameParam::MOD_RULE) == GameParam::TRUE_STATE) { m_mod_rule = true; }
	else { m_mod_rule = false; }

	//�єz�𗘗p���邩�ǂ����̃t���O
	if (_pram.getParam(GameParam::SAIHAI_RULE) == GameParam::TRUE_STATE) {
		m_field.player1_avatar_num = 1;
		m_field.player2_avatar_num = 1;
	}

	//�������肩�ǂ����̃t���O
	if (_pram.getParam(GameParam::SELF_HARM_RULE) == GameParam::TRUE_STATE) { m_self_harm_rule = true; }
	else { m_self_harm_rule = false; }
}

void GameScene::m_selectMove()
{
	//�T�E���h��炷
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1)
	{
		PlaySoundMem(m_sound_hand_select, DX_PLAYTYPE_BACK);
	}
	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1)
	{
		PlaySoundMem(m_sound_hand_cancel, DX_PLAYTYPE_BACK);
	}

	//�������[�����Ȃ��Ȃ�΃t���O���I�t�ɂ���
	if (m_self_harm_rule == false) { m_use_self_hurm = false; }

	//�єz�̏���
	if (m_field.player1_avatar_num != 0) 
	{
		if (m_use_saihai % 3 == 1 || m_use_saihai % 3 == 2) 
		{
			//���L�[�������ꂽ��J�E���^���񂵂ďI��
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1) {
				m_use_saihai++;
				return;
			}

			//X�L�[�������ꂽ��I��
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1) {
				m_use_saihai = 0;
				return;
			}

			//�єz���ʂ��Z�o
			MatchField _low;
			MatchField _high;
			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW, m_field, _low, m_mod_rule, m_self_harm_rule) == false) {
				m_use_saihai = 0;
				return;
			}
			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH, m_field, _high, m_mod_rule, m_self_harm_rule) == false) {
				m_use_saihai = 0;
				return;
			}

			//HIGH��LOW���������Ȃ�΍єz���I��
			if (_low == _high && m_use_saihai % 3 == 2) {
				m_use_saihai = 0;
				return;
			}

			//Z�L�[�������ꂽ��Ֆʂ��m�肵�ďI��
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
			{
				//���Ֆʂ𐶐�����push
				m_pushNewFieldbyCommand((m_use_saihai % 3 == 1) ? VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW : VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH);

				//�J�E���^��S�ď���������
				m_which_player = 0;
				m_which_one_player1 = 0;
				m_which_one_player2 = 0;
				m_use_self_hurm = false;
				m_use_saihai = 0;
				return;
			}

			//�єz�I�𒆂Ȃ�Ό��̏��������Ȃ�
			return;
		}
		else if(m_use_saihai % 3 == 0)
		{
			//���L�[�������ꂽ��J�E���^���񂵂ďI��
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) == 1) {
				m_use_saihai++;
				MatchField _low;
				if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW, m_field, _low, m_mod_rule, m_self_harm_rule) == false) { m_use_saihai = 0; }
				return;
			}
		}
		else { m_use_saihai = 0; }
	}

	//�����̘r��I�������ԂȂ��
	if (m_which_player == 0)
	{
		m_use_self_hurm = false;

		if (m_field.player1.first == 0) { //�Ў肪���݂��Ȃ��Ȃ�ΌŒ�
			m_which_one_player1 = 1;
		}
		else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) {	
			//�L�[���͂ɂ���ĕω�������
			m_which_one_player1++;
		}

		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1)
		{
			if ((m_field.player1.first != 0 && m_which_one_player1 % 2 == 0) || (m_field.player1.second != 0 && m_which_one_player1 % 2 == 1)) {
				//���L�[�������ꂽ���A���ꂪ0�łȂ��Ȃ�ΌŒ肷��
				m_which_player = 1;

				if (m_field.player2.first == 0) { m_which_one_player2 = 1; }
			}
		}
	}
	else {
		//X�{�^���ŃL�����Z������
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_X) == 1) {
			m_which_player = 0;
			m_which_one_player2 = 0;
			m_use_self_hurm = false;
			return;
		}

		//�������[��
		if (m_self_harm_rule == true) 
		{ 
			if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) {
				if (m_use_self_hurm == true) { 
					m_use_self_hurm = false;
					m_which_one_player2 = 1;
				}
				else {
					if (m_which_one_player2 % 2 == 0) { 
						m_use_self_hurm = true; 
						if (m_field.player1.first == 0 || m_field.player1.second == 0) {
							m_use_self_hurm = false;
							m_which_one_player2 = 1;
						}
					}
					else if (m_which_one_player2 % 2 == 1 && m_field.player2.first == 0 && (m_field.player1.first != 0 && m_field.player1.second != 0)) {
						m_use_self_hurm = true;
					}
					else { m_which_one_player2 = 0; }
				}
			}
			else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) 
			{
				if (m_use_self_hurm == true) {
					m_use_self_hurm = false;
					m_which_one_player2 = 0;
				}
				else {
					if (m_which_one_player2 % 2 == 1) { 
						m_use_self_hurm = true; 
						if (m_field.player1.first == 0 || m_field.player1.second == 0) {
							m_use_self_hurm = false;
							m_which_one_player2 = 0;
						}
					}
					else { m_which_one_player2 = 1; }
				}
			}

			//�I�����Ă���̂��O�Ȃ�ΌŒ�
			if (m_field.player2.first == 0 && m_use_self_hurm == false) { 
				m_which_one_player2 = 1;
			}
		}
		//�ʏ탋�[��
		else { 
			if (m_field.player2.first == 0) { //�I�����Ă���̂��O�Ȃ�ΌŒ�
				m_which_one_player2 = 1;
			}
			else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) {
				m_which_one_player2++;
			}
		}

		// Z�L�[�������ꂽ�Ȃ�Ό���
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) { 

			int temp_cmd = 0;

			//�O���U�����Ȃ�
			if ((m_field.player2.first != 0 && m_which_one_player2 % 2 == 0) || (m_field.player2.second != 0 && m_which_one_player2 % 2 == 1))
			{
				//�R�}���h�����߂�
				if (m_use_self_hurm == true) {
					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_SELF; }
					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_SELF; }
				}
				else if (m_which_one_player2 % 2 == 0) {
					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_TO_1; }
					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_TO_1; }
				}
				else {
					if (m_which_one_player1 % 2 == 0) { temp_cmd = VariousFunctionsForMatchGame::COMMAND_1_TO_2; }
					else { temp_cmd = VariousFunctionsForMatchGame::COMMAND_2_TO_2; }
				}

				//�A�j����ǉ�����
				m_pushNewFieldbyCommand(temp_cmd);

				//�J�E���^��S�ď���������
				m_which_player = 0;
				m_which_one_player1 = 0;
				m_which_one_player2 = 0;
				m_use_self_hurm = false;
				m_use_saihai = 0;
			}
		}
	}
}

void GameScene::m_selectEnenmy()
{
	MatchField _new;

	//�V�Ֆʂ𐶐�
	_new = m_field;

	if (VariousFunctionsForMatchGame::matchGameCOM(m_enemy_level, m_field, _new, m_self_harm_rule, m_mod_rule) == false) {
		Parameter _p;
		mp_listenerInterface->deleteNowScene(_p);
		printfDx("Gamescene Class ���G�̔Ֆʐ����֐����G���[���N�����܂���\n���j���[��ʂɖ߂�܂�");
	}

	//�V�����Ֆʂ�}��
	m_pushNewField(_new);
}


void GameScene::m_pushNewField(MatchField& _new)
{
	m_newfield_data = _new;	//�f�[�^���󂯎��

	//�A�j����ǉ�
	m_anime.addAnime(4);
	m_anime.addAnimeOption(m_field, _new);
	
	m_newfield_type = 1;	//�^�C�v��ύX
}

void GameScene::m_pushNewFieldbyCommand(int _cmd)
{
	m_newfield_cmd = _cmd;	//�f�[�^���󂯎��

	//�A�j����ǉ�
	m_anime.addAnime(4);
	m_anime.addAnimeOption2(m_field, _cmd);

	m_newfield_type = 2;	//�^�C�v��ύX
}

void GameScene::m_pushNewFieldExecute()
{
	//�t�B�[���h�f�[�^����X�V����ꍇ
	if (m_newfield_type == 1) 
	{
		//���O��ǉ�
		m_logDraw.pushLogByField(m_newfield_data);

		//�t�B�[���h���X�V
		m_field = m_newfield_data;

		//�^�[���𑝂₷
		m_turn++;
	}
	//�R�}���h����X�V����ꍇ
	else if (m_newfield_type == 2) 
	{
		//���Ֆʂ̐���
		MatchField _temp;
		VariousFunctionsForMatchGame::executeCommand(m_newfield_cmd, m_field, _temp, m_mod_rule, m_self_harm_rule); //�R�}���h�����s

		//���O��ǉ�
		m_logDraw.pushLogByField(_temp);

		//�t�B�[���h���X�V
		m_field = _temp;

		//�^�[���𑝂₷
		m_turn++;
	}

	m_newfield_type = 0;
	return;
}
