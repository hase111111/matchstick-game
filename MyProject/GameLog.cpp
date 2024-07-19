#include "GameLog.h"
#include "Font.h"
#include "DxLib.h"
#include "Define.h"
#include "Keyboard.h"

GameLog::GameLog() : m_DISPLAY_LOG_MAX(5)
{
	m_font_16 = Font::getIns()->getFontHandle("data/font/PixelMplus10_size16.dft");	
}

bool GameLog::update()
{
	//上下キーで表示するログを切り替える処理
	if (m_log.size() > DISPLAY_STR) 
	{
		if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1 || Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) 
		{
			which_field_display++;
		}
	}

	//同盤面が既に4回以上出ているならばFALSEを返す
	for (auto &i : m_field_count)
	{
		if (i.second >= VariousFunctionsForMatchGame::SENNICHITE) { return false; }
	}

	return true;
}

void GameLog::getFieldList(std::vector<MatchField>& _field)
{
	for (auto &i : m_field_list)
	{
		_field.push_back(i);
	}
}

void GameLog::draw(const MatchField _field, const int _turn, const bool _player_is_first, const bool _mod_rule, const bool _self_harm_rule, const int _enemy_level) const
{
	//背景
	DrawBox(Define::WIN_SIZEX * 9 / 32, 0, 0, Define::WIN_SIZEY, GetColor(0xc3, 0xc3, 0xc3), TRUE);
	DrawBox(Define::WIN_SIZEX * 23 / 32, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0xc3, 0xc3, 0xc3), TRUE);

	int _centerx = (Define::WIN_SIZEX * 23 / 32 + Define::WIN_SIZEX) / 2;
	int temp = 0;
	std::string temp_str = "";

	//盤面状況のアナウンス
	{
		temp = GetDrawStringWidthToHandle("=現在の盤面=", 13, m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 3 / 64, GetColor(0, 0, 0), m_font_16, "=現在の盤面=");
	}

	//ターン
	{
		temp_str = std::to_string(_turn) + "ターン目";
		if (_field.turn) { temp_str += " あなたの番です"; }
		else { temp_str += " あいての番です"; }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 7 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());
	}

	//盤面状況
	{
		if (_player_is_first) { temp_str = "あなた(先手)[" + std::to_string(_field.player1.first) + "," + std::to_string(_field.player1.second) + "]"; }
		else { temp_str = "あなた(後手)[" + std::to_string(_field.player1.first) + "," + std::to_string(_field.player1.second) + "]"; }
		if (_field.player1_avatar_num > 0) { temp_str += ",采配残り" + std::to_string(_field.player1_avatar_num); }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 12 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());

		if (_player_is_first) { temp_str = "あいて(後手) [" + std::to_string(_field.player2.first) + "," + std::to_string(_field.player2.second) + "]"; }
		else { temp_str = "あいて(先手) [" + std::to_string(_field.player2.first) + "," + std::to_string(_field.player2.second) + "]"; }
		if (_field.player2_avatar_num > 0) { temp_str += ",采配残り" + std::to_string(_field.player2_avatar_num); }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 15 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());
	}

	//特殊ルール
	{
		temp_str = "MOD 5 ルール...";
		if (_mod_rule) { temp_str += "あり"; }
		else { temp_str += "なし"; }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 21 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());

		temp_str = "自傷 ルール...";
		if (_self_harm_rule) { temp_str += "あり"; }
		else { temp_str += "なし"; }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 24 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());
	}

	//CPUレベル
	{
		temp_str = "CPU LEVEL ...";
		if (_enemy_level > 100) { temp_str += "REPLAY"; }
		else if (_enemy_level % 4 == 0) { temp_str += "EASY"; }
		else if (_enemy_level % 4 == 1) { temp_str += "NORMAL"; }
		else if (_enemy_level % 4 == 2) { temp_str += "HARD"; }
		else { temp_str += "IMPOSSIBLE"; }
		temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), m_font_16);
		DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 30 / 64, GetColor(0, 0, 0), m_font_16, temp_str.c_str());
	}

	//操作方法
	{
		const int posy = 37;
		std::string str = "";

		str = "=操作方法=";
		DrawFormatStringToHandle(_centerx - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * posy / 64, GetColor(0, 0, 0), m_font_16, str.c_str());

		str = "・左右キーで選択    ";
		DrawFormatStringToHandle(_centerx - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * (posy + 4) / 64, GetColor(0, 0, 0), m_font_16, str.c_str());

		str = "・Ｚキーで決定      ";
		DrawFormatStringToHandle(_centerx - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * (posy + 7) / 64, GetColor(0, 0, 0), m_font_16, str.c_str());

		str = "・Ｘキーでキャンセル";
		DrawFormatStringToHandle(_centerx - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * (posy + 10) / 64, GetColor(0, 0, 0), m_font_16, str.c_str());

		str = "・Ｃキーで采配　　　";
		DrawFormatStringToHandle(_centerx - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * (posy + 13) / 64, GetColor(0, 0, 0), m_font_16, str.c_str());
	}

	//ログ
	m_drawLog();

	//ログの切り替えアナウンス
	if (m_log.size() > DISPLAY_STR) {
		DrawBox(Define::WIN_SIZEX * 9 / 32, Define::WIN_SIZEY * 123 / 128, 0, Define::WIN_SIZEY, GetColor(0xa3, 0xa3, 0xa3), TRUE);

		std::string str = "上下キーで切り替え" + std::to_string(which_field_display % 2 + 1) + "/2";

		const int CHAR_SIZE = 18;
		DrawFormatStringToHandle(Define::WIN_SIZEX * 9 / 64 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 4 / 64 + CHAR_SIZE * 27, GetColor(0, 0, 0), m_font_16, str.c_str());
	}
}

void GameLog::pushLog(std::string _log)
{
	//int型の数値と抱き合わせのデータを作る
	std::pair<int, std::string> temp;

	temp.first = 1;
	temp.second = _log;

	//プッシュする
	m_log.push_back(temp);

	//大量のデータが挿入された場合次ページに切り替える
	if (m_log.size() > DISPLAY_STR) { which_field_display = 1; }
}

void GameLog::pushLogByField(const MatchField _field)
{
	//フィールドを追加する
	m_field_list.push_back(_field);

	//フィールドの数を追加
	m_field_count[_field]++;

	//文字を追加する
	std::string str = "";

	if (_field.turn == true)str += "○";
	str += "貴方[" + std::to_string(_field.player1.first) + "," + std::to_string(_field.player1.second) + "] ";

	if (_field.turn == false)str += "○";
	str += "敵[" + std::to_string(_field.player2.first) + "," + std::to_string(_field.player2.second) + "] ";

	if (_field.player1_avatar_num != 0 || _field.player2_avatar_num != 0) {
		str += "采配[" + std::to_string(_field.player1_avatar_num) + "," + std::to_string(_field.player2_avatar_num) + "]";
	}

	//int型の数値と抱き合わせのデータを作る
	std::pair<int, std::string> temp;

	temp.first = m_field_count[_field];
	temp.second = str;

	//プッシュする
	m_log.push_back(temp);

	//大量のデータが挿入された場合次ページに切り替える
	if (m_log.size() > DISPLAY_STR) { which_field_display = 1; }
}

void GameLog::m_drawLog() const
{
	int _centerx = Define::WIN_SIZEX * 9 / 32 / 2;
	int temp = 0;

	temp = GetDrawStringWidthToHandle("=ログ=", 7, m_font_16);
	DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 3 / 64, GetColor(0, 0, 0), m_font_16, "=ログ=");

	const int CHAR_SIZE = 18;//新しいもののみ表示したい

	//m_DISPLAY_LOG_MAX
	for (int i = 0; i < m_log.size(); i++)
	{
		if (m_log.size() > DISPLAY_STR && which_field_display % 2 == 1)
		{
			if (i >= DISPLAY_STR)
			{
				temp = GetDrawStringWidthToHandle(m_log.at(i).second.c_str(), (int)m_log.at(i).second.size(), m_font_16);

				int color = GetColor(0, 0, 0);
				if (m_log.at(i).first == VariousFunctionsForMatchGame::SENNICHITE - 2) { color = GetColor(0xff, 0xa5, 0x00); }
				else if (m_log.at(i).first == VariousFunctionsForMatchGame::SENNICHITE - 1) { color = GetColor(0x80, 0x00, 0x00); }
				else if (m_log.at(i).first >= VariousFunctionsForMatchGame::SENNICHITE) { color = GetColor(0x00, 0x00, 0x8b); }

				DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 4 / 64 + CHAR_SIZE * (i + 1 - DISPLAY_STR), color, m_font_16, m_log.at(i).second.c_str());
			}
		}
		else if (i < DISPLAY_STR)
		{
			temp = GetDrawStringWidthToHandle(m_log.at(i).second.c_str(), (int)m_log.at(i).second.size(), m_font_16);

			int color = GetColor(0, 0, 0);
			if (m_log.at(i).first == VariousFunctionsForMatchGame::SENNICHITE - 2) { color = GetColor(0xff, 0xa5, 0x00); }
			else if (m_log.at(i).first == VariousFunctionsForMatchGame::SENNICHITE - 1) { color = GetColor(0x80, 0x00, 0x00); }
			else if (m_log.at(i).first >= VariousFunctionsForMatchGame::SENNICHITE) { color = GetColor(0x00, 0x00, 0x8b); }

			DrawFormatStringToHandle(_centerx - temp / 2, Define::WIN_SIZEY * 4 / 64 + CHAR_SIZE * (i + 1), color, m_font_16, m_log.at(i).second.c_str());
		}
	}
}
