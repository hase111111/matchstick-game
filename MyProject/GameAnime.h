#pragma once
#include "MatchGameCommon.h"

class GameAnime
{
public:
	GameAnime();
	~GameAnime() = default;

	void init(bool _self, bool _mod, bool _set_anime_cut = false);
	void addAnime(const int _command);
	void addAnimeOption(MatchField _old, MatchField _new);
	void addAnimeOption2(MatchField _old, int _hand_cmd);
	bool update();
	void draw() const;
	bool isEndTime() const;

private:
	//列挙子ハックで定数を宣言
	enum { COMMAND_MAX = 20 };

	int m_counter = 0;		//アニメーションのカウンタ
	int m_command = 0;		//どのアニメーションを再生するかどうかのコマンドを格納する
	int m_ANIME_END_TIMES[COMMAND_MAX] = {};	//各アニメーションごとの終了時間を格納する

	bool m_self_harm = false, m_mod_rule = false;
	int m_hand_cmd = -1;
	MatchField m_old, m_new;

	//アニメーションをカットするフラグ
	bool m_anime_cut_flag = false;

	//フォントハンドル
	int m_font_32 = 0;

	//画像ハンドル
	int m_gr_hand[6] = {};

	//サウンドハンドル
	int m_sound_attack = 0;
	int m_sound_start = 0;

	//各種アニメーション
	void m_drawAnime00() const;
	void m_drawAnime01() const;
	void m_drawAnime02() const;
	void m_drawAnime03() const;
	void m_drawAnime04() const;
	void m_drawAnime05() const;
	void m_drawAnime06() const;
	void m_drawAnime07() const;
	void m_drawAnime08() const;

	void m_drawAnimeAttackBack() const;
	void m_drawAnimeAttackOldHand() const;
	void m_drawAnimeAttackHitHand(int _start_cnt, int _end_cnt) const;
	void m_drawAnimeSelfAttackHitHand(int _start_cnt, int _end_cnt) const;
	void m_drawAnimeAttackChar() const;
	void m_drawAnimeSelfAttackChar() const;
};

/*
攻撃 or 采配

采配
　1手

攻撃
　どっちの手か?
　どこへの攻撃か?
　計算結果の表示
　最適化(並び替え)

*/


