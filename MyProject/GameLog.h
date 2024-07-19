#pragma once
#include<vector>
#include<map>
#include<string>
#include"MatchGameCommon.h"

class GameLog
{
public:
	GameLog();
	~GameLog() = default;

	//この関数がfalseを返す時引き分けとなっている
	bool update();
	void getFieldList(std::vector<MatchField>& _field);
	void draw(const MatchField _field, const int _turn, const bool _player_is_first, const bool _mod_rule, const bool _self_harm_rule, const int _enemy_level) const;
	void pushLog(std::string _log);
	void pushLogByField(const MatchField _field);

private:
	const int m_DISPLAY_LOG_MAX;

	//データ
	std::vector<std::pair<int, std::string>> m_log;
	std::vector<MatchField> m_field_list;
	std::map<MatchField, int> m_field_count;

	//表示する文字についてのデータ
	const int DISPLAY_STR = 26;
	int which_field_display = 0;

	//フォント
	int m_font_16;

	//関数
	void m_drawLog() const;
};