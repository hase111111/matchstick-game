#pragma once
#include<string>

class MenuDrawBack
{
public:
	MenuDrawBack();

	void update();
	void draw() const;

private:

	const std::string MESSAGE = "�E�y�L�[�Ō���@�@�E�����L�[�őI���@�@�E�����L�[�{ctrl�L�[�Ń��j���[���ڐ؂�ւ��@�@�EEsc�L�[�Ń^�C�g���ɖ߂�@�@";

	int m_font_handle = 0;
	int m_counter = 0;
};
