#pragma once
#include"AbstractScene.h"
#include"MatchGameCommon.h"
#include"SceneChangeEffect.h"
#include"GameHand.h"
#include"GameLog.h"
#include"GameAnime.h"

class GameScene : public AbstractScene 
{
public:
	GameScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	SceneChangeEffect m_sceneChange;
	GameHand m_handDraw;
	GameLog m_logDraw;
	GameAnime m_anime;

	//�T�E���h�n���h��
	int m_sound_hand_select = 0;
	int m_sound_hand_cancel = 0;

	//�}�b�`�Q�[���̔Ֆ�
	MatchField m_field;
	int m_turn = 1;
	bool m_player_is_first;
	bool m_mod_rule;
	bool m_self_harm_rule;

	//�s���I�𒆂Ɏg�p����ϐ��y�уt���O
	bool m_is_selecting_now = false;
	int m_which_player = 0;
	int m_which_one_player1 = 0;
	int m_which_one_player2 = 0;
	bool m_use_self_hurm = false;
	int m_use_saihai = 0;

	//�GCPU�̃��x��
	int m_enemy_level = 0;

	//�֐�
	void m_initField(const Parameter& _pram);
	void m_selectMove();
	void m_selectEnenmy();

	//�A�j���[�V�����Đ����ɔՖʂ����ւ���
	void m_pushNewField(MatchField& _new);
	void m_pushNewFieldbyCommand(int _cmd);
	void m_pushNewFieldExecute();
	int m_newfield_type = 0;
	MatchField m_newfield_data;
	int m_newfield_cmd = 0;

	//�V�[���`�F���W�p�̃t���O
	bool m_changescene_flag = false;
	int m_changescene_which = 0;
};
