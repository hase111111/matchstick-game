#pragma once
#include <vector>
#include "MatchGameCommon.h"

class ResultDrawHand
{
public:
	ResultDrawHand();

	void init(const std::vector<MatchField> _list);
	void update(const int _select);
	void draw() const;

private:

	//��̃O���t�B�b�N�n���h��
	int m_gr_hand[7];

	//�t�B�[���h�̃��X�g
	std::vector<MatchField> m_field_list;

	//�\�����Ă���t�B�[���h
	int m_select_field = 0;

	//�������������ǂ����̃t���O
	bool m_init_flag = false;
};
