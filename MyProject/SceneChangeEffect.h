#pragma once

class SceneChangeEffect
{
public:
	SceneChangeEffect();
	~SceneChangeEffect() = default;

	void init(const int _mode);
	bool update();
	void draw() const;

private:
	int m_counter = 0;	//�A�j���[�V�����𓮂����J�E���^
	int m_mode = 0;		//�ǂ̃A�j���[�V�����𓮂������̃t���O

	//�T�E���h�n���h��
	int m_sound_fade_in = 0;
	int m_sound_fade_out = 0;

	const int m_WIN_DIV = 6;	//��ʂ�6��������
	const int m_END_TIME = 50;	//�A�j���[�V�������s������
	const int m_COLOR;
};