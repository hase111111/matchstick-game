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

	//���̊֐���false��Ԃ������������ƂȂ��Ă���
	bool update();
	void getFieldList(std::vector<MatchField>& _field);
	void draw(const MatchField _field, const int _turn, const bool _player_is_first, const bool _mod_rule, const bool _self_harm_rule, const int _enemy_level) const;
	void pushLog(std::string _log);
	void pushLogByField(const MatchField _field);

private:
	const int m_DISPLAY_LOG_MAX;

	//�f�[�^
	std::vector<std::pair<int, std::string>> m_log;
	std::vector<MatchField> m_field_list;
	std::map<MatchField, int> m_field_count;

	//�\�����镶���ɂ��Ẵf�[�^
	const int DISPLAY_STR = 26;
	int which_field_display = 0;

	//�t�H���g
	int m_font_16;

	//�֐�
	void m_drawLog() const;
};