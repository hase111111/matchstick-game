//#pragma once
//#include "Parameter.h"
//#include "SceneEnum.h"
//#include <string>
//#include <vector>
//
//class MenuBox
//{
//public:
//	MenuBox();
//
//	bool update(enumScene& _scene, Parameter& _param);
//	bool getGameEnd() const;
//	void draw() const;
//
//private:
//	//処理をするためのカウンタ
//	int m_counter = 0;
//	const int m_MENU_NUM = 4;
//
//	int m_command_counter = 0;
//	const int m_BATTLE_NUM = 6;
//
//	//戦闘の設定を記録する変数・フラグ
//	int m_battle_first = 0;
//	int m_battle_cpu = 3;
//	bool m_battle_mod = true;
//	bool m_battle_self = true;
//	bool m_battle_saihai = true;
//
//	//リプレイの処理のための変数・フラグ
//	bool m_file_load_flag = false;
//	std::vector<std::string> m_file_list;
//	int m_file_select = 0;
//	std::string m_file_error_log = "";
//
//	//設定シーンの変数・フラグ
//	int m_setting_vol = 0;
//	bool m_setting_win_ful = false;
//	bool m_setting_anime_cut = false;
//	bool m_game_end_flag = false;
//
//	//四角形の大きさ
//	const int BOX_X;
//	const int BOX_Y;
//
//	//フォントハンドル
//	int m_font_32 = 0;
//	int m_font_20 = 0;
//
//	//サウンドハンドル
//	int m_sound_select = 0;
//	int m_sound_select2 = 0;
//	int m_sound_cancel = 0;
//
//	//処理関数
//	void m_updateSetting();
//	void m_resetReplayFile();
//	bool m_getReplayFileList();
//
//	//描画関数
//	void m_drawBox() const;
//	void m_drawString() const;
//	void m_drawString_VS() const;
//	void m_drawString_Rule() const;
//	void m_drawString_Replay() const;
//	void m_drawString_String() const;
//};