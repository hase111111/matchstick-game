#pragma once
#include <string>
#include <vector>

struct HandAnime
{
	double x = 0.0;
	double base_x = 0.0;
	double y = 0.0;
	double v = 3.0;
	int gr = 0;
};

//�^�C�g����ʂ̗��œ����w�i�摜
class TitleAnime
{
public:
	TitleAnime();
	~TitleAnime() = default;

	bool update();
	void draw() const;

private:
	//�A�j���[�V���������̂��߂̕ϐ�
	std::vector<HandAnime> m_hand_anime;
	const double m_HAND_SIZEX;		//��̉摜�̉���
	const double m_HAND_SIZEY;		//��̉摜�̏c��

	//�^�C�g����ʂ̕�����\�����邽�߂̕ϐ�
	int m_font_64, m_font_32, m_font_20;
	const std::string m_GAMETITLE;
	const int m_GAMETITLE_STR_LEN;
	const std::string m_ANNOUNCE;
	const int m_ANNOUNCE_STR_LEN;
	int m_counter;
	const std::string m_COPYRIGHT;
	const int m_COPYRIGHT_STR_LEN;

	//�摜�̃n���h��
	int m_gr_back;
	int m_gr_hand[7];

	//���̑�����p�֐�
	void m_InitHandAnime();
	void m_updateHandAnime();
	void m_drawHandAnime() const;
	void m_DrawGameName() const;
};
