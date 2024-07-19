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
	//フィールドリストを読み込む
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

	//ルールを読み込む
	m_mod_rule = mod;
	m_self_rule = self;

	//初期化済みフラグを立てる
	m_init_flag = true;
}

void ResultString::update(const int select_field)
{
	//初期化が終わっていないなら終了
	if (m_init_flag == false) { return; }

	//選択した盤面を受け取る
	m_select_field = select_field;

	//評価する盤面と選択盤面が違うなら同一にする
	if (m_select_field != m_hyouka_field) {
		m_Hyouka();
	}
}

void ResultString::draw(const bool _replay, const bool _replay_fail) const
{
	//初期化が終わっていないなら終了
	if (m_init_flag == false) { return; }

	//ログを表示
	m_drawLog(_replay, _replay_fail);

	//盤面の部分の文字の描画
	m_drawField();

	//点数
	m_drawEvaluation();
}


void ResultString::m_drawLog(const bool _replay, const bool _replay_fail) const
{
	int Log_HalfX = Define::WIN_SIZEX * 17 / 128;
	std::string str = "";
	
	//画面上部のアナウンス
	str = "ログ";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 7 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);

	//画面下部のアナウンス
	const int MOJIKAN_ANA = Define::WIN_SIZEY / 33;
	str = "ＭＯＤ:";
	str += (m_mod_rule == true) ? "あり" : "なし";
	str += " 自傷:";
	str += (m_self_rule == true) ? "あり " : "なし ";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = "上下キーで選択　　　　\n";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = (_replay == true) ? "リプレイ保存済み　　　\n" : "Ｚキーでリプレイ保存　\n";
	if (_replay_fail == true) { str = "リプレイ保存失敗　　　\n"; }
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA * 2, str.c_str(), GetColor(0, 0, 0), m_font_16);
	str = "ESCキーで戻る　　　　 \n";
	DrawStringToHandle(Log_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 106 / 128 + MOJIKAN_ANA * 3, str.c_str(), GetColor(0, 0, 0), m_font_16);

	//盤面リスト
	const int HYOUJIDEKIRU_SAIDAISUU = 25;
	const int MOJIKAN = Define::WIN_SIZEY / 34;
	int y = 0, color = 0;
	for (int i = 0; i < m_field_list.size(); i++)
	{
		str = std::to_string(i + 1) + "ターン目:";
		str += m_getStrForField(m_field_list.at(i));

		if (str.size() > 23)
		{
			while (str.size() > 20) { str.pop_back(); }
			str += "―";
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

	//勝敗を書く
	if (m_field_list.back().doesWinFirstPlayer() == true)
	{
		color = GetColor(0xff, 0, 0);
		str = "あなたの勝利"; 
	}
	else  if (m_field_list.back().doesWinSecondPlayer() == true) 
	{
		color = GetColor(0, 0, 0xff);
		str = "あなたの敗北"; 
	}
	else 
	{
		color = GetColor(0, 0, 0);
		str = "同一盤面が4回現れたので引き分け"; 
	}
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_32) / 2, Define::WIN_SIZEY / 16, str.c_str(), color, m_font_32);

	//表示しているフィールドの状況を表示する
	if (m_select_field >= 0 && m_select_field < m_field_list.size()) 
	{
		str = " " + std::to_string(m_select_field + 1) + "ターン目  ";
		str += (m_field_list.at(m_select_field).turn == true) ? "あなたの番" : "敵の番";
		DrawStringToHandle(Define::WIN_SIZEX * 34 / 128, Define::WIN_SIZEY * 93 / 128, str.c_str(), GetColor(0, 0, 0), m_font_16);
	}

	//フィールドの文字
	str = "あなた";
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 87 / 128, str.c_str(), GetColor(0,0,0), m_font_16);
	str = "敵";
	DrawStringToHandle(Field_HalfX - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_16) / 2, Define::WIN_SIZEY * 21 / 128, str.c_str(), GetColor(0,0,0), m_font_16);
}

void ResultString::m_drawEvaluation() const
{
	std::string str = "";
	int _tempx = 0;
	int Result_HalfX = Define::WIN_SIZEX * 34 / 128;
	int Result_HalfY = Define::WIN_SIZEY * 103 / 128;

	//選択している盤面が範囲外ならば何もしない
	if (m_select_field >= 0 && m_select_field < m_field_list.size())
	{
		//現在の盤面 → 次の盤面
		{
			if (m_field_list.at(m_select_field).turn == true) { str = " あなたの番/ "; }
			else { str = " 敵の番/ "; }
			str += m_getStrForField(m_field_list.at(m_select_field));

			if (m_select_field + 1 < (int)m_field_list.size())
			{
				//次盤面が存在しているならば
				str += +" → ";
				str += m_getStrForField(m_field_list.at((size_t)m_select_field + 1));
			}
			else
			{
				//次盤面がぞんざいしていないならば
				if (m_field_list.at(m_select_field).doesWinFirstPlayer() == true) { str += " あなたの勝利"; }
				else if (m_field_list.at(m_select_field).doesWinSecondPlayer() == true) { str += " あなたの敗北"; }
				else { str += " 同一盤面4回目なので引き分け"; }
			}

			DrawStringToHandle(Result_HalfX, Result_HalfY, str.c_str(), GetColor(0, 0, 0), m_font_16); 
		}

		//採点
		{
			//選択している盤面と評価している盤面が同じ時のみ実行
			if (m_hyouka_field == m_select_field) 
			{
				str = " ";

				if (m_hyouka_next_num == 0) //盤面が一つのみ
				{
					str += "勝敗が決定したため、次盤面は存在しない";
				}
				else if (m_hyouka_next_num > 0) //次盤面が存在する
				{
					if (m_field_list.at(m_select_field).turn == true) { str += "あなたの"; }
					else { str += "敵の"; }

					str += "行動/";
					if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_SAIHAI_HIGH || m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_SAIHAI_LOW) { str += "采配"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_SELF) { str += "自傷(右に攻撃)"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_SELF) { str += "自傷(左に攻撃)"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_TO_1) { str += "左手で左手に攻撃"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_1_TO_2) { str += "左手で右手に攻撃"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_TO_1) { str += "右手で左手に攻撃"; }
					else if (m_hyouka_command == VariousFunctionsForMatchGame::COMMAND_2_TO_2) { str += "右手で右手に攻撃"; }
					str += " この行動は" + std::to_string(m_hyouka_point) + "点";
					str += " (勝率 あなた" + std::to_string(m_hyouka_percent) + "% 敵" + std::to_string(100 - m_hyouka_percent) + "%)";
				}

				DrawStringToHandle(Result_HalfX, Result_HalfY + Define::WIN_SIZEY / 20, str.c_str(), GetColor(0x60, 0x60, 0x60), m_font_16);
			}
		}

		//最高評価盤面を表示する
		{
			str = " ";

			//次盤面が一つしかないならば
			if (m_hyouka_next_num == 0) {
			}
			else if (m_hyouka_next_num == 1) 
			{
				str += "次盤面はこれのみ";
			}
			//選択した手と最善手が一致しているならば
			else if (m_hyouka_point == m_hyouka_saizente_point) 
			{
				str += "この行動は最善手";
			}
			else 
			{
				str += "この盤面での最善手 ";
				str += m_getStrForField(m_hyouka_Saizente);
				str += " 最善手の得点/" + std::to_string(m_hyouka_saizente_point) + "点";
			}

			DrawStringToHandle(Result_HalfX, Result_HalfY + Define::WIN_SIZEY / 10, str.c_str(), GetColor(0x60, 0x60, 0x60), m_font_16);
		}
	}
}


std::string ResultString::m_getStrForField(const MatchField _field) const
{
	std::string str = "あなた[";
	str += std::to_string(_field.player1.first) + "," + std::to_string(_field.player1.second) + "]敵[";
	str += std::to_string(_field.player2.first) + "," + std::to_string(_field.player2.second) + "]";

	//采配が残っているならば
	if (_field.player1_avatar_num != 0 || _field.player2_avatar_num != 0) {
		str += " 采配[" + std::to_string(_field.player1_avatar_num) + "," + std::to_string(_field.player2_avatar_num) + "]";
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
		//評価する盤面を更新
		m_hyouka_field = m_select_field;

		std::vector<MatchField> _list;	//次盤面を代入するリスト

		//次盤面生成
		VariousFunctionsForMatchGame::makeNextFieldList(_list, m_field_list.at(m_hyouka_field), m_mod_rule, m_self_rule);

		//次盤面の数を代入
		m_hyouka_next_num = (int)_list.size();

		if (m_select_field + 1 >= (int)m_field_list.size()) { m_hyouka_next_num = 0; }	//引き分けを判断する処理

		//次盤面の数が1つ以上ならば採点してあげる
		if (m_hyouka_next_num >= 1 && m_select_field + 1 < (int)m_field_list.size())
		{
			//採点する
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

			//コマンドを調べる
			m_hyouka_command = VariousFunctionsForMatchGame::getCommand(m_field_list.at(m_select_field), m_field_list.at((size_t)m_select_field + 1), m_mod_rule, m_self_rule);
		}

		//最善手を取得
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
