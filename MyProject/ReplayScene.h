#pragma once
#include "AbstractScene.h"
#include"SceneChangeEffect.h"
#include"MatchGameCommon.h"
#include<vector>
#include"GameAnime.h"
#include"GameHand.h"
#include"GameLog.h"

class ReplayScene : public AbstractScene
{
public:
	ReplayScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;

	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	//�N���X
	SceneChangeEffect m_sceneChange;	//�V�[���`�F���W�̃G�t�F�N�g
	GameAnime m_gameAnime;
	GameHand m_gameHand;
	GameLog m_gameLog;

	//�Q�[���p�̃p�����[�^
	bool m_mod_rule = false;		//MOD 5���[�����K�p����Ă��邩�̃t���O
	bool m_self_rule = false;		//�������[�����̗p����Ă��邩�̃t���O
	std::vector<MatchField> m_field_list;	//�t�B�[���h�̃��X�g

	//�}�b�`�Q�[���̔Ֆ�
	MatchField m_field;
	int m_turn = 0;
	bool m_player_is_first;

	//�ϐ��E�t���O
	bool m_illegal_field = false;	//�s���ȔՖʂ��ǂ����̃t���O
	bool m_scene_change = false;	//���̃t���O�����������ɃV�[����߂�

	//�֐�
	void m_loadParam(const Parameter parameter);	//�p�����[�^���󂯎��
	bool m_isIllegalFieldList(const std::vector<MatchField>& _field) const;		//�s���ȃt�B�[���h���X�g���ǂ����𒲂ׂ�
};
