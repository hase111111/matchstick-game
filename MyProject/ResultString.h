#pragma once
#include "MatchGameCommon.h"
#include <vector>
#include <string>
#include "MatchGameCommon.h"

class ResultString
{
public:
	ResultString();

	void init(const std::vector<MatchField> _list, const bool mod, const bool self);
	void update(const int select_field);
	void draw(const bool _replay, const bool _replay_fail) const;

private:

	//フォント
	int m_font_16 = 0;
	int m_font_32 = 0;

	//関数
	void m_drawLog(const bool _replay, const bool _replay_fail) const;
	void m_drawField() const;
	void m_drawEvaluation() const;
	std::string m_getStrForField(const MatchField _field) const;
	int m_getPointForSaiten(const int _point) const;
	void m_Hyouka();

	//変数・フラグ
	std::vector<MatchField> m_field_list;
	std::vector<int> m_field_sennitite_list;
	bool m_mod_rule = false;
	bool m_self_rule = false;
	bool m_init_flag = false;

	int m_select_field = 0;

	int m_hyouka_field = -1;
	int m_hyouka_next_num = 0;
	int m_hyouka_point = 0;
	int m_hyouka_percent = 0;
	int m_hyouka_command = 0;
	MatchField m_hyouka_Saizente;
	int m_hyouka_saizente_point = 0;
};