#include "ResultString.h"
#include "Font.h"
#include "Define.h"
#include "DxLib.h"

ResultString::ResultString()
{
	m_font_16 = myLoadFont("data/font/PixelMplus10_size16.dft");
	m_font_32 = myLoadFont("data/font/PixelMplus10_size32.dft");
}

void ResultString::init(const std::vector<MatchField> _list, const bool mod, const bool self)
{
	//�t�B�[���h���X�g��ǂݍ���
	for (auto &i : _list)
	{
		m_field_list.push_back(i);
	}

	std::map<MatchField, int> _counter;
	for (auto& i : _list)
	{
		_counter[i]++;
		m_field_sennitite_list.push_back(_counter[i]);
	}

	//���[����ǂݍ���
	m_mod_rule = mod;
	m_self_rule = self;

	//�������ς݃t���O�𗧂Ă�
	m_init_flag = true;
}

void ResultString::update(const int select_field)
{
	//���������I����Ă��Ȃ��Ȃ�I��
	if (m_init_flag == false) { return; }

	//�I�������Ֆʂ��󂯎��
	m_select_field = select_field;

	//�]������ՖʂƑI��Ֆʂ��Ⴄ�Ȃ瓯��ɂ���
	if (m_select_field != m_hyouka_field) {
		m_Hyouka();
	}
}

void ResultString::draw(const bool _replay, const bool _replay_fail) const
{
	//���������I����Ă��Ȃ��Ȃ�I��
	if (m_init_flag == false) { return; }

	//���O��\��
	m_drawLog(_replay, _replay_fail);

	//�Ֆʂ̕����̕����̕`��
	m_drawField();

	//�_��
	m_drawEvaluation();
}


void ResultString::m_drawLog(const bool _replay, const bool _replay_fail) const
{
	int Log_HalfX = Define::WIN_SIZEX * 17 / 128;
	std::string str = "";
	
	//��ʏ㕔�̃A�i�E���X
	str = "���O";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 7 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);

	//��ʉ����̃A�i�E���X
	const int MOJIKAN_ANA = Define::WIN_SIZEY / 33;
	str = "�l�n�c:";
	str += (m_mod_rule == true) ? "����" : "�Ȃ�";
	str += " ����:";
	str += (m_self_rule == true) ? "���� " : "�Ȃ� ";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = "�㉺�L�[�őI���@�@�@�@\n";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = (_replay == true) ? "���v���C�ۑ��ς݁@�@�@\n" : "�y�L�[�Ń��v���C�ۑ��@\n";
	if (_replay_fail == true) { str = "���v���C�ۑ����s�@�@�@\n"; }
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA * 2, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = "ESC�L�[�Ŗ߂�@�@�@�@ \n";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA * 3, str.c_str(), GetColor(0, 0, 0), m_font_16);

	//�Ֆʃ��X�g
	const int HYOUJIDEKIRU_SAIDAISUU = 25;
	const int MOJIKAN = Define::WIN_SIZEY / 34;
	int y = 0, color = 0;
	for (int i = 0; i < m_field_list.size(); i++)
	{
		str = std::to_string(i + 1) + "�^�[����:";
		str += m_getStrForField(m_field_list.at(i));

		if (str.size() > 23)
		{
			while (str.size() > 20) { str.pop_back(); }
			str += "�\";
		}

		y = Define::WIN_SIZEY * 13 / 128 + MOJIKAN * (i % HYOUJIDEKIRU_SAIDAISUU);
		color = GetColor(0, 0, 0);
		if (m_field_sennitite_list.at(i) == VariousFunctionsForMatchGame::SENNICHITE - 2) { color = GetColor(0xff, 0xa5, 0x00); }
		else if (m_field_sennitite_list.at(i) == VariousFunctionsForMatchGame::SENNICHITE - 1) { color = GetColor(0x80, 0x00, 0x00); }
		else if (m_field_sennitite_list.at(i) == VariousFunctionsForMatchGame::SENNICHITE) { color = GetColor(0x00, 0x00, 0x8b); }

		if((m_select_field < HYOUJIDEKIRU_SAIDAISUU && i < HYOUJIDEKIRU_SAIDAISUU) || (m_select_field >= HYOUJIDEKIRU_SAIDAISUU && i >= HYOUJIDEKIRU_SAIDAISUU))
		{
			DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, y, str.c_str(), color, m_font_16);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(pow(sin(2 * Define::PI * GetNowCount() / 1500), 2) * 128.0));
	const int BOX_X = Define::WIN_SIZEX * 26 / 128;
	y = Define::WIN_SIZEY * 27 / 256 + MOJIKAN * (m_select_field % HYOUJIDEKIRU_SAIDAISUU);
	DrawBox(Log_HalfX - BOX_X / 2, y, Log_HalfX + BOX_X / 2, y + Define::WIN_SIZEY / 43, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultString::m_drawField() const
{
	std::string str = "";
	int color = 0;
	int Field_HalfX = Define::WIN_SIZEX * 79 / 128;

	//���s������
	if (m_field_list.back().doesWinFirstPlayer() == true)
	{
		color = GetColor(0xff, 0, 0);
		str = "���Ȃ��̏���"; 
	}
	else  if (m_field_list.back().doesWinSecondPlayer() == true) 
	{
		color = GetColor(0, 0, 0xff);
		str = "���Ȃ��̔s�k"; 
	}
	else 
	{
		color = GetColor(0, 0, 0);
		str = "����Ֆʂ�4�񌻂ꂽ�̂ň�������"; 
	}
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY / 16, str.c_str(), color, m_font_32);

	//�\�����Ă���t�B�[���h�̏󋵂�\������
	if (m_select_field >= 0 && m_select_field < m_field_list.size()) 
	{
		str = " " + std::to_string(m_select_field + 1) + "�^�[����  ";
		str += (m_field_list.at(m_select_field).turn == true) ? "���Ȃ��̔�" : "�G�̔�";
		DrawStringToHandle(Define::WIN_SIZEX * 34 / 128, Define::WIN_SIZEY * 93 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);
	}

	//�t�B�[���h�̕���
	str = "���Ȃ�";
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 87 / 128, str.c_str(), GetColor(0,0,0), m_font_16);
	str = "�G";
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 21 / 128, str.c_str(), GetColor(0,0,0), m_font_16);
}

void ResultString::m_drawEvaluation() const
{
	std::string str = "";
	int _tempx = 0;
	int Result_HalfX = Define::WIN_SIZEX * 34 / 128;
	int Result_HalfY = Define::WIN_SIZEY * 103 / 128;

	//�I�����Ă���Ֆʂ��͈͊O�Ȃ�Ή������Ȃ�
	if (m_select_field >= 0 && m_select_field < m_field_list.size())
	{
		//���݂̔Ֆ� �� ���̔Ֆ�
		{
			if (m_field_list.at(m_select_field).turn == true) { str = " ���Ȃ��̔�/ "; }
			else { str = " �G�̔�/ "; }
			str += m_getStrForField(m_field_list.at(m_select_field));

			if (m_select_field + 1 < (int)m_field_list.size())
			{
				//���Ֆʂ����݂��Ă���Ȃ��
				str += +" �� ";
				str += m_getStrForField(m_field_list.at((size_t)m_select_field + 1));
			}
			else
			{
				//���Ֆʂ����񂴂����Ă��Ȃ��Ȃ��
				if (m_field_list.at(m_select_field).doesWinFirstPlayer() == true) { str += " ���Ȃ��̏���"; }
				else if (m_field_list.at(m_select_field).doesWinSecondPlayer() == true) { str += " ���Ȃ��̔s�k"; }
				else { str += " ����Ֆ�4��ڂȂ̂ň�������"; }
			}

			DrawStringToHandle(Result_HalfX, Result_HalfY, str.c_str(), GetColor(0, 0, 0), m_font_16); 
		}

		//�̓_
		{
			//�I�����Ă���Ֆʂƕ]�����Ă���Ֆʂ��������̂ݎ��s
			if (m_hyouka_field == m_select_field) 
			{
				str = " ";

				if (m_hyouka_next_num == 0) //�Ֆʂ���̂�
				{
					str += "���s�����肵�����߁A���Ֆʂ͑��݂��Ȃ�";
				}
				else if (m_hyouka_next_num > 0) //���Ֆʂ����݂���
				{
					if (m_field_list.at(m_select_field).turn == true) { str += "���Ȃ���"; }
					else { str += "�G��"; }

					str += "�s��/";
					if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH || m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW) { str += "�єz"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_SELF) { str += "����(�E�ɍU��)"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_SELF) { str += "����(���ɍU��)"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_TO_1) { str += "����ō���ɍU��"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_TO_2) { str += "����ŉE��ɍU��"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_TO_1) { str += "�E��ō���ɍU��"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_TO_2) { str += "�E��ŉE��ɍU��"; }
					str += " ���̍s����" + std::to_string(m_hyouka_point) + "�_";
					str += " (���� ���Ȃ�" + std::to_string(m_hyouka_percent) + "% �G" + std::to_string(100 - m_hyouka_percent) + "%)";
				}

				DrawStringToHandle(Result_HalfX, Result_HalfY + Define::WIN_SIZEY / 20, str.c_str(), GetColor(0x60, 0x60, 0x60), m_font_16);
			}
		}

		//�ō��]���Ֆʂ�\������
		{
			str = " ";

			//���Ֆʂ�������Ȃ��Ȃ��
			if (m_hyouka_next_num == 0) {
			}
			else if (m_hyouka_next_num == 1) 
			{
				str += "���Ֆʂ͂���̂�";
			}
			//�I��������ƍőP�肪��v���Ă���Ȃ��
			else if (m_hyouka_point == m_hyouka_saizente_point) 
			{
				str += "���̍s���͍őP��";
			}
			else 
			{
				str += "���̔Ֆʂł̍őP�� ";
				str += m_getStrForField(m_hyouka_Saizente);
				str += " �őP��̓��_/" + std::to_string(m_hyouka_saizente_point) + "�_";
			}

			DrawStringToHandle(Result_HalfX, Result_HalfY + Define::WIN_SIZEY / 10, str.c_str(), GetColor(0x60, 0x60, 0x60), m_font_16);
		}
	}
}


std::string ResultString::m_getStrForField(const MatchField _field) const
{
	std::string str = "���Ȃ�[";
	str += std::to_string(_field.player1.first) + "," + std::to_string(_field.player1.second) + "]�G[";
	str += std::to_string(_field.player2.first) + "," + std::to_string(_field.player2.second) + "]";

	//�єz���c���Ă���Ȃ��
	if (_field.player1_avatar_num != 0 || _field.player2_avatar_num != 0) {
		str += " �єz[" + std::to_string(_field.player1_avatar_num) + "," + std::to_string(_field.player2_avatar_num) + "]";
	}
	
	return str;
}

int ResultString::m_getPointForSaiten(const int _point) const
{
	int res = 0;
	const int MANTEN = 100;
	const int GOMI = 0;
	const int MANNAKA = 50;

	if (_point > VariousFunctionsForMatchGame::WIN / 2) 
	{
		res = MANTEN;
		res -= VariousFunctionsForMatchGame::WIN - _point;
	}
	else if (_point < VariousFunctionsForMatchGame::LOSE / 2) 
	{
		res = GOMI;
		res -= VariousFunctionsForMatchGame::LOSE - _point;
	}
	else {
		res = MANNAKA; 
	}

	return res;
}

void ResultString::m_Hyouka()
{
	if (0 <= m_select_field && m_select_field < (int)m_field_list.size()) 
	{
		//�]������Ֆʂ��X�V
		m_hyouka_field = m_select_field;

		std::vector<MatchField> _list;	//���Ֆʂ������郊�X�g

		//���Ֆʐ���
		VariousFunctionsForMatchGame::makeNextFieldList(_list, m_field_list.at(m_hyouka_field), m_mod_rule, m_self_rule);

		//���Ֆʂ̐�����
		m_hyouka_next_num = (int)_list.size();

		if (m_select_field + 1 >= (int)m_field_list.size()) { m_hyouka_next_num = 0; }	//���������𔻒f���鏈��

		//���Ֆʂ̐���1�ȏ�Ȃ�΍̓_���Ă�����
		if (m_hyouka_next_num >= 1 && m_select_field + 1 < (int)m_field_list.size())
		{
			//�̓_����
			if (m_mod_rule == true) 
			{
				m_hyouka_point = VariousFunctionsForMatchGame::evaluationFunctionForMod(m_field_list.at((size_t)m_select_field + 1), m_field_list.at(m_select_field).turn, m_self_rule, 0);
				m_hyouka_point = m_getPointForSaiten(m_hyouka_point);
				m_hyouka_percent = VariousFunctionsForMatchGame::evaluationFunctionForMod(m_field_list.at((size_t)m_select_field + 1), true, m_self_rule, 0);
				m_hyouka_percent = m_getPointForSaiten(m_hyouka_percent);
			}
			else 
			{
				m_hyouka_point = VariousFunctionsForMatchGame::evaluationFunction(m_field_list.at((size_t)m_select_field + 1), m_field_list.at(m_select_field).turn, m_self_rule, 0);
				m_hyouka_point = m_getPointForSaiten(m_hyouka_point);
				m_hyouka_percent = VariousFunctionsForMatchGame::evaluationFunction(m_field_list.at((size_t)m_select_field + 1), true, m_self_rule, 0);
				m_hyouka_percent = m_getPointForSaiten(m_hyouka_percent);
			}

			//�R�}���h�𒲂ׂ�
			m_hyouka_command = VariousFunctionsForMatchGame::getCommand(m_field_list.at(m_select_field), m_field_list.at((size_t)m_select_field + 1), m_mod_rule, m_self_rule);
		}

		//�őP����擾
		VariousFunctionsForMatchGame::matchGameCOM(3, m_field_list.at(m_hyouka_field), m_hyouka_Saizente, m_self_rule, m_mod_rule);
		if (m_mod_rule == true) 
		{
			m_hyouka_saizente_point = VariousFunctionsForMatchGame::evaluationFunctionForMod(m_hyouka_Saizente, m_field_list.at(m_select_field).turn, m_self_rule, 0);
			m_hyouka_saizente_point = m_getPointForSaiten(m_hyouka_saizente_point);
		}
		else 
		{
			m_hyouka_saizente_point = VariousFunctionsForMatchGame::evaluationFunction(m_hyouka_Saizente, m_field_list.at(m_select_field).turn, m_self_rule);
			m_hyouka_saizente_point = m_getPointForSaiten(m_hyouka_saizente_point);
		}
	}
	else 
	{
		m_hyouka_field = -1;
	}
}
