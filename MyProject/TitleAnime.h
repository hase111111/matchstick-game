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

//タイトル画面の裏で動く背景画像
class TitleAnime
{
public:
	TitleAnime();
	~TitleAnime() = default;

	bool update();
	void draw() const;

private:
	//アニメーションする手のための変数
	std::vector<HandAnime> m_hand_anime;
	const double m_HAND_SIZEX;		//手の画像の横幅
	const double m_HAND_SIZEY;		//手の画像の縦幅

	//タイトル画面の文字を表示するための変数
	int m_font_64, m_font_32, m_font_20;
	const std::string m_GAMETITLE;
	const int m_GAMETITLE_STR_LEN;
	const std::string m_ANNOUNCE;
	const int m_ANNOUNCE_STR_LEN;
	int m_counter;
	const std::string m_COPYRIGHT;
	const int m_COPYRIGHT_STR_LEN;

	//画像のハンドル
	int m_gr_back;
	int m_gr_hand[7];

	//その他制御用関数
	void m_InitHandAnime();
	void m_updateHandAnime();
	void m_drawHandAnime() const;
	void m_DrawGameName() const;
};
