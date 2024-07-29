//#include "MenuBox.h"
//#include"DxLib.h"
//#include"define.h"
//#include"Keyboard.h"
//#include"Font.h"
//#include"Sound.h"
//#include"RuleParam.h"
//#include"GameParam.h"
//#include"Setting.h"
//
//MenuBox::MenuBox() : 
//	BOX_X(Define::WIN_SIZEX * 53 / 64), 
//	BOX_Y(Define::WIN_SIZEY * 3 / 32)
//{
//	//フォントのロード
//	m_font_32 = myLoadFont("data/font/PixelMplus10_size32.dft");
//	m_font_20 = myLoadFont("data/font/PixelMplus10_size20.dft");
//
//	//サウンドのロード
//	m_sound_select = Sound::getIns()->myLoadSound("data/sound/selecting.mp3");
//	m_sound_select2 = Sound::getIns()->myLoadSound("data/sound/selecting2.mp3");
//	m_sound_cancel = Sound::getIns()->myLoadSound("data/sound/cancel.mp3");
//
//	//設定のロード
//	m_updateSetting();
//}
//
//bool MenuBox::update(enumScene& _scene, Parameter& _param)
//{
//	//シーン切り替えの処理
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1 && (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) > 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RCONTROL) > 0)) 
//	{
//		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//		m_counter++;
//		m_command_counter = 0;
//
//		m_updateSetting();	//設定を読み込みなおす
//		m_resetReplayFile();//ファイルをアンロードする
//	}
//	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1 && (Keyboard::getIns()->getPressingCount(KEY_INPUT_LCONTROL) > 0 || Keyboard::getIns()->getPressingCount(KEY_INPUT_RCONTROL) > 0)) 
//	{
//		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//		m_counter += m_MENU_NUM - 1;
//		m_command_counter = 0;
//
//		m_updateSetting();	//設定を読み込みなおす
//		m_resetReplayFile();//ファイルをアンロードする
//	}
//	//下ボタンを押したとき
//	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_DOWN) == 1) 
//	{
//		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//		m_command_counter += 1;	//項目を変更
//
//		//対戦の下に移動
//		if (m_command_counter > 5) 
//		{
//			m_counter += 1;
//			m_command_counter = 0;
//
//			m_updateSetting();	//設定を読み込みなおす
//			m_resetReplayFile();//ファイルをアンロードする
//		}
//
//		//項目の数が少ないリプレイのための処理
//		if (m_counter % m_MENU_NUM == 2 && m_command_counter % 6 >= 4) 
//		{
//			m_counter += 1;
//			m_command_counter = 0;
//
//			m_updateSetting();	//設定を読み込みなおす
//			m_resetReplayFile();//ファイルをアンロードする
//		}
//	}
//	//上ボタンを押したとき
//	else if (Keyboard::getIns()->getPressingCount(KEY_INPUT_UP) == 1) 
//	{
//		PlaySoundMem(m_sound_select, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//		m_command_counter -= 1;	//項目を変更
//
//		//対戦の上に移動
//		if (m_command_counter < 0) 
//		{
//			m_counter += m_MENU_NUM - 1;
//			m_command_counter = 5;
//
//			m_updateSetting();	//設定を読み込みなおす
//			m_resetReplayFile();//ファイルをアンロードする
//		}
//
//		//項目の数が少ないリプレイのための処理
//		if (m_counter % m_MENU_NUM == 2 && m_command_counter % 6 >= 4)
//		{
//			m_command_counter = 3;
//		}
//	}
//
//	//左右キーによる処理
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_RIGHT) == 1) 
//	{
//		//項目vsCPUを選択中
//		if (m_counter % m_MENU_NUM == 0)
//		{
//			PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//			if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 1; }					//先行プレイヤー
//			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 1; }				//CPU
//			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai; }	//采配
//			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//自傷
//			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5
//		}
//		//項目リプレイを選択中
//		else if (m_counter % m_MENU_NUM == 2) 
//		{
//			if (m_command_counter % 4 == 1 && m_file_load_flag == true)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				m_file_select++;
//			}
//		}
//		//項目設定を選択中
//		else if (m_counter % m_MENU_NUM == 3)
//		{
//			//音量
//			if (m_command_counter % m_BATTLE_NUM == 2)
//			{
//				m_setting_vol += 5;
//				m_setting_vol = (m_setting_vol > 100) ? 100 : m_setting_vol;
//
//				//音量を仮設定して再生
//				Sound::getIns()->changeVolume(m_setting_vol);
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//			}
//			//ウィンドウモード
//			else if (m_command_counter % m_BATTLE_NUM == 3)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//
//				m_setting_win_ful = !m_setting_win_ful;
//			}
//			//アニメをカット
//			else if (m_command_counter % m_BATTLE_NUM == 4)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//
//				m_setting_anime_cut = !m_setting_anime_cut;
//			}
//		}
//	}
//	else if(Keyboard::getIns()->getPressingCount(KEY_INPUT_LEFT) == 1) 
//	{
//		//項目vsCPUを選択中
//		if (m_counter % m_MENU_NUM == 0)
//		{
//			PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//			if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 2; }					//先行プレイヤー
//			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 3; }				//CPU
//			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai;  }	//采配
//			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//自傷
//			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5
//		}
//		//項目リプレイを選択中
//		else if (m_counter % m_MENU_NUM == 2)
//		{
//			if (m_command_counter % 4 == 1 && m_file_load_flag == true)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				m_file_select += (int)m_file_list.size() - 1;
//			}
//		}
//		//項目設定を選択中
//		else if (m_counter % m_MENU_NUM == 3)
//		{
//			//音量
//			if (m_command_counter % m_BATTLE_NUM == 2) 
//			{
//				m_setting_vol -= 5;
//				m_setting_vol = (m_setting_vol < 0) ? 0 : m_setting_vol;
//
//				//音量を仮設定して再生
//				Sound::getIns()->changeVolume(m_setting_vol);
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//			}
//			//ウィンドウモード
//			else if (m_command_counter % m_BATTLE_NUM == 3)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//
//				m_setting_win_ful = !m_setting_win_ful;
//			}
//			//アニメをカット
//			else if (m_command_counter % m_BATTLE_NUM == 4)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//
//				m_setting_anime_cut = !m_setting_anime_cut;
//			}
//		}
//	}
//
//	//Escキーによる処理
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_ESCAPE) == 1) 
//	{
//		PlaySoundMem(m_sound_cancel, DX_PLAYTYPE_BACK);
//
//		_scene = enumScene::title;
//		_param.resetParam();
//		return true;
//	}
//
//	//Zキーによる決定
//	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_Z) == 1) 
//	{
//		//vs CPU項目の戦闘開始を選択時
//		if (m_counter % m_MENU_NUM == 0) 
//		{
//			if (m_command_counter % 6 == 0) 
//			{
//				//シーンの設定
//				_scene = enumScene::game;
//
//				//パラメータの設定
//				_param.resetParam();
//
//				//先手の算出
//				if (m_battle_first % 3 == 1 || (m_battle_first % 3 == 0 && GetRand(1) == 0)) { _param.setParam(GameParam::PLAYER_IS_FIRST, GameParam::TRUE_STATE); }
//				else { _param.setParam(GameParam::PLAYER_IS_FIRST, GameParam::FALSE_STATE); }
//
//				//CPUレベル
//				if (m_battle_cpu % 4 == 0) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_EASY); }
//				else if (m_battle_cpu % 4 == 1) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_NORMAL); }
//				else if (m_battle_cpu % 4 == 2) { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_HARD); }
//				else { _param.setParam(GameParam::ENEMY_LEVEL, GameParam::ENEMY_LEVEL_IMPOSSIBLE); }
//
//				//MODルールの設定
//				if (m_battle_mod == true) { _param.setParam(GameParam::MOD_RULE, GameParam::TRUE_STATE); }
//				else { _param.setParam(GameParam::MOD_RULE, GameParam::FALSE_STATE); }
//
//				//自傷の設定
//				if (m_battle_self == true) { _param.setParam(GameParam::SELF_HARM_RULE, GameParam::TRUE_STATE); }
//				else { _param.setParam(GameParam::SELF_HARM_RULE, GameParam::FALSE_STATE); }
//
//				//采配の設定
//				if (m_battle_saihai == true) { _param.setParam(GameParam::SAIHAI_RULE, GameParam::TRUE_STATE); }
//				else { _param.setParam(GameParam::SAIHAI_RULE, GameParam::FALSE_STATE); }
//
//				return true;
//			}
//			else if (m_command_counter % m_BATTLE_NUM == 1) { m_battle_first += 1; }					//先行プレイヤー
//			else if (m_command_counter % m_BATTLE_NUM == 2) { m_battle_cpu += 1; }				//CPU
//			else if (m_command_counter % m_BATTLE_NUM == 3) { m_battle_saihai = !m_battle_saihai; }	//采配
//			else if (m_command_counter % m_BATTLE_NUM == 4) { m_battle_self = !m_battle_self; }	//自傷
//			else if (m_command_counter % m_BATTLE_NUM == 5) { m_battle_mod = !m_battle_mod; }	//MOD 5
//
//			//選択音を鳴らす}
//			if (m_command_counter % m_BATTLE_NUM != 0) { PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK); }
//		}
//		//ルール確認の項目を選択中
//		else if (m_counter % m_MENU_NUM == 1) 
//		{
//			//シーンの設定
//			_scene = enumScene::rule;
//
//			//パラメータの設定
//			_param.resetParam();
//			if (m_command_counter % 6 == 0) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_BASIC); }
//			else if (m_command_counter % 6 == 1) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SLEF); }
//			else if (m_command_counter % 6 == 2) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SAIHAI); }
//			else if (m_command_counter % 6 == 3) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_MOD_5); }
//			else if (m_command_counter % 6 == 4) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_SENRYAKU); }
//			else if (m_command_counter % 6 == 5) { _param.setParam(RuleParam::WHICH_RULE, RuleParam::STATE_OTHER); }
//
//			return true;
//		}
//		//リプレイの項目を選択中
//		else if (m_counter % m_MENU_NUM == 2)
//		{
//			//読み込み
//			if (m_command_counter % 4 == 0 && m_file_load_flag == false) 
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				//フラグを立てる
//				m_file_load_flag = true;
//
//				//読み込む
//				if (m_getReplayFileList() == false) {
//					m_file_error_log = "ファイルを読み込めませんでした";
//				}
//				else {
//					m_file_error_log = "読み込み成功 " + std::to_string(m_file_list.size()) + "ファイル";
//				}
//
//			}
//			//ファイル選択
//			else if (m_command_counter % 4 == 1 && m_file_load_flag == true) 
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				m_file_select++;
//			}
//			//ファイル分析
//			else if (m_command_counter % 4 == 2 && m_file_load_flag == true && m_file_list.size() != 0)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				//リプレイファイルの読み込み
//				std::vector<MatchField> m_field_list_param;
//				bool m_mod_rule_param = false;
//				bool m_self_harm_param = false;
//				std::string m_file_path_param = "./replay/" + m_file_list.at(m_file_select % m_file_list.size());
//
//				if (VariousFunctionsForMatchGame::inputFieldList(m_file_path_param, m_field_list_param, m_mod_rule_param, m_self_harm_param) == false)
//				{
//					m_file_error_log = "リプレイファイルの読み込みに失敗";
//				}
//				else 
//				{
//					//読み込みに成功した場合パラメータをセットして読みこみ
//					_scene = enumScene::result;
//
//					_param.resetParam();
//					_param.setFieldParam(m_field_list_param);
//					_param.setParam(GameParam::MOD_RULE, (m_mod_rule_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
//					_param.setParam(GameParam::SELF_HARM_RULE, (m_self_harm_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
//					_param.setParam(GameParam::RESULT_BACK_NUM, 1);
//					return true;
//				}
//			}
//			//ファイル再生
//			else if (m_command_counter % 4 == 3 && m_file_load_flag == true && m_file_list.size() != 0)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//選択音を鳴らす
//
//				//リプレイファイルの読み込み
//				std::vector<MatchField> m_field_list_param;
//				bool m_mod_rule_param = false;
//				bool m_self_harm_param = false;
//				std::string m_file_path_param = "./replay/" + m_file_list.at(m_file_select % m_file_list.size());
//
//				if (VariousFunctionsForMatchGame::inputFieldList(m_file_path_param, m_field_list_param, m_mod_rule_param, m_self_harm_param) == false)
//				{
//					m_file_error_log = "リプレイファイルの読み込みに失敗";
//				}
//				else
//				{
//					//読み込みに成功した場合パラメータをセットして読みこみ
//					_scene = enumScene::replay;
//
//					_param.resetParam();
//					_param.setFieldParam(m_field_list_param);
//					_param.setParam(GameParam::MOD_RULE, (m_mod_rule_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
//					_param.setParam(GameParam::SELF_HARM_RULE, (m_self_harm_param == true) ? GameParam::TRUE_STATE : GameParam::FALSE_STATE);
//					return true;
//				}
//			}
//		}
//		//設定の項目を選択中
//		else if (m_counter % m_MENU_NUM == 3) 
//		{
//			//設定を保存する
//			if (m_command_counter % 6 == 0) 
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);	//音楽を再生
//				Setting::getIns()->saveSettingFile(m_setting_vol, m_setting_win_ful, m_setting_anime_cut);	//設定を保存する
//				Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());	//音量設定
//			}
//			//設定を初期化する
//			else if (m_command_counter % 6 == 1) 
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//				//デフォの設定に戻す
//				m_setting_vol = Setting::getIns()->getSettingVol(true);
//				m_setting_win_ful = Setting::getIns()->getSettingFulWin(true);
//				m_setting_anime_cut = Setting::getIns()->getSettingAnime(true);
//			}
//			//音量
//			else if (m_command_counter % 6 == 2)
//			{
//				m_setting_vol += 10;
//				m_setting_vol = (m_setting_vol > 100) ? (m_setting_vol % 100) : m_setting_vol;
//
//				//音量を仮設定して再生
//				Sound::getIns()->changeVolume(m_setting_vol);
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//			}
//			//フルスクリーン
//			else if (m_command_counter % 6 == 3)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//				m_setting_win_ful = !m_setting_win_ful;
//			}
//			//アニメ
//			else if (m_command_counter % 6 == 4)
//			{
//				PlaySoundMem(m_sound_select2, DX_PLAYTYPE_BACK);
//				m_setting_anime_cut = !m_setting_anime_cut;
//			}
//			//ゲーム終了を選択する
//			else if (m_command_counter % 6 == 5)
//			{
//				m_game_end_flag = true;
//			}
//		}
//	}
//
//	return false;
//}
//
//bool MenuBox::getGameEnd() const
//{
//	return m_game_end_flag;
//}
//
//void MenuBox::draw() const
//{
//	//背景の四角を描画する
//	m_drawBox();
//
//	//文字
//	m_drawString();
//}
//
////処理関係の関数
//void MenuBox::m_updateSetting()
//{
//	//設定ファイルのロード
//	m_setting_vol = Setting::getIns()->getSettingVol();
//	m_setting_win_ful = Setting::getIns()->getSettingFulWin();
//	m_setting_anime_cut = Setting::getIns()->getSettingAnime();
//
//	//設定ファイルからの音量設定
//	Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());	
//}
//
//void MenuBox::m_resetReplayFile()
//{
//	//ファイルリストを空にする
//	m_file_list.clear();
//
//	//フラグをへし折る
//	m_file_load_flag = false;
//
//	//選択中のファイルを0に
//	m_file_select = 0;
//
//	//ログを空にする
//	m_file_error_log = "";
//}
//
//bool MenuBox::m_getReplayFileList()
//{
//	HANDLE hFind;
//	WIN32_FIND_DATA win32fd;
//	std::string search_name = "replay\\*.dat";
//
//	hFind = FindFirstFile(search_name.c_str(), &win32fd);
//
//	if (hFind == INVALID_HANDLE_VALUE) {
//		return false;
//	}
//
//	/* 指定のディレクトリ以下のファイル名をファイルがなくなるまで取得する */
//	do {
//		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//			/* ディレクトリの場合は何もしない */
//			printf("directory\n");
//		}
//		else {
//			/* ファイルが見つかったらVector配列に保存する */
//			m_file_list.push_back(win32fd.cFileName);
//		}
//	} while (FindNextFile(hFind, &win32fd));
//
//	FindClose(hFind);
//
//	return true;
//}
//
////描画関係の関数
//void MenuBox::m_drawString() const
//{
//	//勝負
//	m_drawString_VS();
//
//	//ルール
//	m_drawString_Rule();
//
//	//リプレイ
//	m_drawString_Replay();
//
//	//設定
//	m_drawString_String();
//}
//
//void MenuBox::m_drawString_VS() const
//{
//	const int POSX = Define::WIN_SIZEX / 10;
//	const int HALF_X = Define::WIN_SIZEX / 2;
//	const int LEFT_MIDDLE = Define::WIN_SIZEX * 26 / 64;
//	const int RIGHT_MIDDLE = Define::WIN_SIZEX * 38 / 64;
//	std::string str;
//
//	//ラベル VS CPU
//	DrawStringToHandle(POSX, Define::WIN_SIZEY * 3 / 40, "vsCPU", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//
//	//選択中 選択肢の表示
//	if (m_counter % m_MENU_NUM == 0)
//	{
//		//Zキーで勝負開始
//		str = "Zキーで勝負開始";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 11 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		//固定される文字を表示する
//		{
//			for (int i = 0; i < 5; i++)
//			{
//				// 中央の :
//				str = ":";
//				DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * (15 + 4 * i) / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//				// 右の < >
//				str = "<            >";
//				DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * (15 + 4 * i) / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//			}
//
//			//左側の文字
//			str = "先行プレイヤー";
//			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 15 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			str = "CPU のレベル";
//			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			str = "采配ルール";
//			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			str = "自傷ルール";
//			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			str = "MOD 5 ルール";
//			DrawStringToHandle(LEFT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//		}
//
//		//選択によって変更される文字
//		{
//			//先行プレイヤー
//			if (m_battle_first % 3 == 0) { str = "ランダム"; }
//			else if (m_battle_first % 3 == 1) { str = "あなた"; }
//			else { str = "敵"; }
//			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 15 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			//CPUのレベル
//			if (m_battle_cpu % 4 == 0) { str = "EASY"; }
//			else if (m_battle_cpu % 4 == 1) { str = "NORMAL"; }
//			else if (m_battle_cpu % 4 == 2) { str = "HARD"; }
//			else { str = "IMPOSSIBLE"; }
//			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			//采配ルール
//			if (m_battle_saihai == true) { str = "ON"; }
//			else { str = "OFF"; }
//			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), (m_battle_saihai == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			//自傷ルール
//			if (m_battle_self == true) { str = "ON"; }
//			else { str = "OFF"; }
//			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), (m_battle_self == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);
//
//			//MOD 5ルール
//			if (m_battle_mod == true) { str = "ON"; }
//			else { str = "OFF"; }
//			DrawStringToHandle(RIGHT_MIDDLE - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), (m_battle_mod == true) ? GetColor(0xff, 0x11, 0x11) : GetColor(0x11, 0x11, 0x11), m_font_20);
//		}
//	}
//}
//
//void MenuBox::m_drawString_Rule() const
//{
//	const int POSX = Define::WIN_SIZEX / 10;
//	const int HALF_X = Define::WIN_SIZEX / 2;
//	std::string str;
//
//	if (m_counter % m_MENU_NUM == 0) {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 24 / 40, "ルール確認", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//	else {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 8 / 40, "ルール確認", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//
//	if (m_counter % m_MENU_NUM == 1) {
//		str = "基本ルール";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 19 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "ローカルルール : 　　采配　　 ";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 23 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "ローカルルール : 　　自傷　　 ";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "ローカルルール : 　　MOD 5　　";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "戦略指南";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "このゲームで採用されていないルールと補足";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//	}
//}
//
//void MenuBox::m_drawString_Replay() const
//{
//	const int POSX = Define::WIN_SIZEX / 10;
//	const int HALF_X = Define::WIN_SIZEX / 2;
//	std::string str;
//	int color = 0;
//
//	if (m_counter % m_MENU_NUM == 0 || m_counter % m_MENU_NUM == 1) {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 29 / 40, "リプレイ", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//	else {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 13 / 40, "リプレイ", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//
//	if (m_counter % m_MENU_NUM == 2) 
//	{
//		//ロードの項目
//		if (m_file_load_flag == false)
//		{ 
//			color = GetColor(0xff, 0, 0);
//			str = "リプレイファイルをロードする";
//		}
//		else 
//		{
//			color = GetColor(0x51, 0x51, 0x51);
//			str = "リプレイファイルのロードに成功しました"; 
//		}
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 27 / 64, str.c_str(), color, m_font_20);
//
//		//リプレイファイルを選択する項目
//		if (m_file_load_flag == false) 
//		{ 
//			color = GetColor(0x51, 0x51, 0x51);
//			str = "リプレイファイルをロードしてください";
//		}
//		else if(m_file_list.size() <= 0)
//		{ 
//			color = GetColor(0x11, 0x11, 0x11);
//			str = "リプレイファイルが存在しません";
//		}
//		else {
//			color = GetColor(0x11, 0x11, 0x11);
//			str = "<　";
//			str += m_file_list.at(m_file_select % m_file_list.size());
//			str += "　>";
//		}
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 31 / 64, str.c_str(), color, m_font_20);
//
//		//れざるとを表示する項目
//		str = "リプレイを分析する";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "リプレイを再生する";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "ファイル読み込みのログ";
//		str += (m_file_error_log.size() == 0) ? "" : ":" + m_file_error_log;
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 45 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		/*
//		* 		str = "戦略指南";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "このゲームで採用されていないルールと補足";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//		*/
//	}
//}
//
//void MenuBox::m_drawString_String() const
//{
//	const int POSX = Define::WIN_SIZEX / 10;
//	const int HALF_X = Define::WIN_SIZEX / 2;
//	const int QUARTER_X = (HALF_X + BOX_X / 2) / 2;
//	std::string str;
//
//	if (m_counter % m_MENU_NUM == 3) {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 18 / 40, "各種設定", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//	else {
//		DrawStringToHandle(POSX, Define::WIN_SIZEY * 34 / 40, "各種設定", GetColor(0xe5, 0xe5, 0xe5), m_font_32);
//	}
//
//	if (m_counter % m_MENU_NUM == 3) 
//	{
//		str = "設定を保存・適用する";
//		int color_code = GetColor(0x11, 0x11, 0x11);
//		//現状のデータと違うなら色を返る
//		if (m_setting_vol != Setting::getIns()->getSettingVol() || m_setting_win_ful != Setting::getIns()->getSettingFulWin() || m_setting_anime_cut != Setting::getIns()->getSettingAnime()) { color_code = GetColor(0xc0, 0x0, 0x0); }
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 35 / 64, str.c_str(), color_code, m_font_20);
//
//		str = "設定を初期化する";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 39 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "　　　　ボリューム設定　　　　";
//		str += ": ＜　　　　　　　　　　　　＞ ";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//		str = std::to_string(m_setting_vol) + "%";
//		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 43 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "フルスクリーン（再起動で適用）";
//		str += ": ＜　　　　　　　　　　　　＞ ";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//		str = (m_setting_win_ful) ? "フルスクリーンで起動" : "ウィンドウモードで起動";
//		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 47 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "　戦闘中のアニメをカットする　";
//		str += ": ＜　　　　　　　　　　　　＞ ";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 51 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//		str = (m_setting_anime_cut) ? "アニメをカットする" : "カットしない";
//		DrawStringToHandle(Define::WIN_SIZEX * 85 / 128 - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 51 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//
//		str = "ゲームを終了する";
//		DrawStringToHandle(HALF_X - GetDrawStringWidthToHandle(str.c_str(), (int)str.size(), m_font_20) / 2, Define::WIN_SIZEY * 55 / 64, str.c_str(), GetColor(0x11, 0x11, 0x11), m_font_20);
//	}
//}
//
//void MenuBox::m_drawBox() const
//{
//	const int HALFX = Define::WIN_SIZEX / 2;
//	const int MINI_BOX_X = BOX_X;
//	const int MINI_BOX_Y = (int)(BOX_Y / 1.6);
//
//	//勝負
//	if (m_counter % m_MENU_NUM == 0) {
//		//選択中
//		int POS1_Y = Define::WIN_SIZEY * 4 / 40;
//		int POS2_Y = Define::WIN_SIZEY * 20 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
//		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS1_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//
//		//点滅する白い箱
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
//		int _miny = Define::WIN_SIZEY * 12 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
//		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//	else {
//		int POS1_Y = Define::WIN_SIZEY * 4 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS1_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS1_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//
//	//ルール
//	if (m_counter % m_MENU_NUM == 0) {
//		int POS2_Y = Define::WIN_SIZEY * 25 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//	else if (m_counter % m_MENU_NUM == 1) {
//		//選択中
//		const int POS2_Y = Define::WIN_SIZEY * 9 / 40;
//		const int POS3_Y = Define::WIN_SIZEY * 25 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
//		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//
//		//点滅する白い箱
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
//		int _miny = Define::WIN_SIZEY * 20 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
//		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//	else {
//		const int POS2_Y = Define::WIN_SIZEY * 9 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS2_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS2_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//
//
//	//リプレイ
//	if (m_counter % m_MENU_NUM == 3) 
//	{
//		const int POS3_Y = Define::WIN_SIZEY * 14 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//	else if (m_counter % m_MENU_NUM == 2) 
//	{
//		//選択中
//		const int POS3_Y = Define::WIN_SIZEY * 14 / 40;
//		const int POS4_Y = Define::WIN_SIZEY * 30 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//
//		//点滅する白い箱
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
//		int _miny = Define::WIN_SIZEY * 28 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
//		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//	else {
//		const int POS3_Y = Define::WIN_SIZEY * 30 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//
//
//	//設定
//	if (m_counter % m_MENU_NUM == 3) 
//	{
//		//選択中
//		const int POS3_Y = Define::WIN_SIZEY * 19 / 40;
//		const int POS4_Y = Define::WIN_SIZEY * 35 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0xa2, 0xa2, 0xa2), TRUE);
//		DrawBox(HALFX - BOX_X / 2, POS3_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS3_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//
//		//点滅する白い箱
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0 * sin(GetNowCount() * 2.0 * Define::PI / 2000) * sin(GetNowCount() * 2.0 * Define::PI / 2000)));
//		int _miny = Define::WIN_SIZEY * 36 / 64 + (Define::WIN_SIZEY * 4 / 64 + Define::WIN_SIZEY / 512) * (m_command_counter % 6);
//		DrawBox(HALFX - MINI_BOX_X / 2, _miny - MINI_BOX_Y / 2, HALFX + MINI_BOX_X / 2, _miny + MINI_BOX_Y / 2, GetColor(0xff, 0xff, 0xff), TRUE);
//		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
//	}
//	else {
//		const int POS4_Y = Define::WIN_SIZEY * 35 / 40;
//		DrawBox(HALFX - BOX_X / 2, POS4_Y - BOX_Y / 2, HALFX + BOX_X / 2, POS4_Y + BOX_Y / 2, GetColor(0x3a, 0x3a, 0x3a), TRUE);
//	}
//}
