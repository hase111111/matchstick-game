#include "GameHand.h"
#include "Image.h"
#include "DxLib.h"
#include "Define.h"
#include "Font.h"

GameHand::GameHand()
{
	//�摜�̓ǂݍ���
	m_gr_hand[0] = myLoadGraph("data/img/hand/0_hand.png");
	m_gr_hand[1] = myLoadGraph("data/img/hand/1_hand.png");
	m_gr_hand[2] = myLoadGraph("data/img/hand/2_hand.png");
	m_gr_hand[3] = myLoadGraph("data/img/hand/3_hand.png");
	m_gr_hand[4] = myLoadGraph("data/img/hand/4_hand.png");
	m_gr_hand[5] = myLoadGraph("data/img/hand/5_hand.png");

	m_gr_arrow = myLoadGraph("data/img/arrow.png");

	//�t�H���g
	m_font_32 = Font::getIns()->getFontHandle("data/font/PixelMplus10_size32.dft");
	m_font_20 = Font::getIns()->getFontHandle("data/font/PixelMplus10_size20.dft");
}

void GameHand::draw(MatchField _field, const bool _select_now, const int _which_player, const int _which_hand_pl1, const int _which_hand_pl2, const bool _self, const int _saihai) const
{
	//�I�𒆂Ȃ�\�������߂� 1.1�`1.35�{�܂�2�b����
	double ex_rate_big = 1.1 + 0.25 * pow(sin(GetNowCount() / 1500.0 * 2 * Define::PI), 2);

	//��̕`��
	if (_select_now == true && _saihai % 3 == 0) {
		if (_which_hand_pl1 % 2 == 0 || _self) { DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 12 / 16, ex_rate_big, 0.0, m_gr_hand[_field.player1.first], TRUE, TRUE, FALSE); }
		else { DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[_field.player1.first], TRUE, TRUE, FALSE); }

		if (_which_hand_pl1 % 2 == 1 || _self) { DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 12 / 16, ex_rate_big, 0.0, m_gr_hand[_field.player1.second], TRUE, FALSE, FALSE); }
		else { DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[_field.player1.second], TRUE, FALSE, FALSE); }

		if (_which_hand_pl2 % 2 == 0 && _which_player == 1 && !_self) { DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 4 / 16, ex_rate_big, 0.0, m_gr_hand[_field.player2.first], TRUE, TRUE, TRUE); }
		else { DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[_field.player2.first], TRUE, TRUE, TRUE); }

		if (_which_hand_pl2 % 2 == 1 && _which_player == 1 && !_self) { DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 4 / 16, ex_rate_big, 0.0, m_gr_hand[_field.player2.second], TRUE, FALSE, TRUE); }
		else { DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[_field.player2.second], TRUE, FALSE, TRUE); }
		
	}
	else {
		DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[_field.player1.first], TRUE, TRUE, FALSE);
		DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 12 / 16, 1.0, 0.0, m_gr_hand[_field.player1.second], TRUE, FALSE, FALSE);
		DrawRotaGraph(Define::WIN_SIZEX * 23 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[_field.player2.first], TRUE, TRUE, TRUE);
		DrawRotaGraph(Define::WIN_SIZEX * 41 / 64, Define::WIN_SIZEY * 4 / 16, 1.0, 0.0, m_gr_hand[_field.player2.second], TRUE, FALSE, TRUE);
	}

	//��̐����𕶎��ŕ\��
	DrawFormatStringToHandle(Define::WIN_SIZEX * 45 / 128, Define::WIN_SIZEY * 14 / 16, GetColor(0, 0, 0), m_font_32, "%d", _field.player1.first);
	DrawFormatStringToHandle(Define::WIN_SIZEX * 82 / 128, Define::WIN_SIZEY * 14 / 16, GetColor(0, 0, 0), m_font_32, "%d", _field.player1.second);
	DrawFormatStringToHandle(Define::WIN_SIZEX * 45 / 128, Define::WIN_SIZEY * 1 / 16, GetColor(0, 0, 0), m_font_32, "%d", _field.player2.first);
	DrawFormatStringToHandle(Define::WIN_SIZEX * 81 / 128, Define::WIN_SIZEY * 1 / 16, GetColor(0, 0, 0), m_font_32, "%d", _field.player2.second);

	//����
	m_drawString();

	//����\��
	bool _saihai_state = (_saihai % 3 == 0) ? false : true;
	m_drawArrow(_which_player, _which_hand_pl1, _which_hand_pl2, _self, _saihai_state);

	//�єz�̕\��
	if (_saihai % 3 == 1 || _saihai % 3 == 2) 
	{
		//���̕\��
		float half_boxx = Define::WIN_SIZEX * 39.0f / 128 / 2;
		float half_boxy = Define::WIN_SIZEX * 17.0f / 128 / 2;
		DrawBoxAA(Define::WIN_SIZEX / 2 - half_boxx, Define::WIN_SIZEY / 2 - half_boxy, Define::WIN_SIZEX / 2 + half_boxx, Define::WIN_SIZEY / 2 + half_boxy, GetColor(0, 0, 0), FALSE, 3.0f);

		//��̕\��
		double _angle = 0.25 * sin(GetNowCount() / 1500.0 * 2 * Define::PI);
		MatchField _saihai_field;
		if (_saihai % 3 == 1) {
			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW, _field, _saihai_field) == true) {
				DrawRotaGraph(Define::WIN_SIZEX * 27 / 64, Define::WIN_SIZEY / 2, 1.0, _angle, m_gr_hand[_saihai_field.player1.first], TRUE, TRUE, FALSE);
				DrawRotaGraph(Define::WIN_SIZEX * 37 / 64, Define::WIN_SIZEY / 2, 1.0, _angle, m_gr_hand[_saihai_field.player1.second], TRUE, FALSE, FALSE);
			}
		}
		else {
			if (VariousFunctionsForMatchGame::executeCommand(VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH, _field, _saihai_field) == true) {
				DrawRotaGraph(Define::WIN_SIZEX * 27 / 64, Define::WIN_SIZEY / 2, 1.0, _angle, m_gr_hand[_saihai_field.player1.first], TRUE, TRUE, FALSE);
				DrawRotaGraph(Define::WIN_SIZEX * 37 / 64, Define::WIN_SIZEY / 2, 1.0, _angle, m_gr_hand[_saihai_field.player1.second], TRUE, FALSE, FALSE);
			}
		}

		//�K�C�h�����̕\��
		std::string _gide = "�єz C�L�[�Ő؂�ւ�";
		DrawFormatStringToHandle(Define::WIN_SIZEX / 2 - GetDrawStringWidthToHandle(_gide.c_str(), (int)_gide.size(), m_font_20) / 2, Define::WIN_SIZEY * 42 / 128, GetColor(0, 0, 0), m_font_20, _gide.c_str());
	}
}

void GameHand::m_drawString() const
{
	//���Ȃ�
	{
		std::string temp_str = "���Ȃ�";
		int temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_32);
		DrawFormatStringToHandle(Define::WIN_SIZEX / 2 - temp / 2, Define::WIN_SIZEY * 15 / 16, GetColor(0, 0, 0), m_font_32, temp_str.c_str());
	}

	//�G
	{
		std::string temp_str = "�G";
		int temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_32);
		DrawFormatStringToHandle(Define::WIN_SIZEX / 2 - temp / 2, 0, GetColor(0, 0, 0), m_font_32, temp_str.c_str());
	}
}

void GameHand::m_drawArrow(const int _which, const int _pl1, const int _pl2, const bool _self, const bool _saihai) const
{
	//�J�E���^�𗘗p���ē_�ł�����
	double alpha = 128.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);

	if (_which == 1 && _saihai == false) 
	{
		if (_self == true) {
			if (_pl1 %2 == 0) {
				DrawRotaGraph(Define::WIN_SIZEX * 64 / 128, Define::WIN_SIZEY * 49 / 64, 1.0, Define::PI / 2, m_gr_arrow, TRUE);
			}
			else {
				DrawRotaGraph(Define::WIN_SIZEX * 64 / 128, Define::WIN_SIZEY * 49 / 64, 1.0, -Define::PI / 2, m_gr_arrow, TRUE);
			}
		}
		else {
			if (_pl1 % 2 == 0) {
				if (_pl2 % 2 == 0) {
					DrawRotaGraph(Define::WIN_SIZEX * 46 / 128, Define::WIN_SIZEY / 2, 1.0, 0.0, m_gr_arrow, TRUE);
				}
				else {
					DrawRotaGraph(Define::WIN_SIZEX * 64 / 128, Define::WIN_SIZEY / 2, 1.0, Define::PI / 4, m_gr_arrow, TRUE);
				}
			}
			else {
				if (_pl2 % 2 == 0) {
					DrawRotaGraph(Define::WIN_SIZEX * 64 / 128, Define::WIN_SIZEY / 2, 1.0, -Define::PI / 4, m_gr_arrow, TRUE);
				}
				else {
					DrawRotaGraph(Define::WIN_SIZEX * 82 / 128, Define::WIN_SIZEY / 2, 1.0, 0.0, m_gr_arrow, TRUE);
				}
			}
		}

	}

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
