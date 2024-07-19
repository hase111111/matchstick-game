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
	//�񋓎q�n�b�N�Œ萔��錾
	enum { COMMAND_MAX = 20 };

	int m_counter = 0;		//�A�j���[�V�����̃J�E���^
	int m_command = 0;		//�ǂ̃A�j���[�V�������Đ����邩�ǂ����̃R�}���h���i�[����
	int m_ANIME_END_TIMES[COMMAND_MAX] = {};	//�e�A�j���[�V�������Ƃ̏I�����Ԃ��i�[����

	bool m_self_harm = false, m_mod_rule = false;
	int m_hand_cmd = -1;
	MatchField m_old, m_new;

	//�A�j���[�V�������J�b�g����t���O
	bool m_anime_cut_flag = false;

	//�t�H���g�n���h��
	int m_font_32 = 0;

	//�摜�n���h��
	int m_gr_hand[6] = {};

	//�T�E���h�n���h��
	int m_sound_attack = 0;
	int m_sound_start = 0;

	//�e��A�j���[�V����
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
�U�� or �єz

�єz
�@1��

�U��
�@�ǂ����̎肩?
�@�ǂ��ւ̍U����?
�@�v�Z���ʂ̕\��
�@�œK��(���ёւ�)

*/


