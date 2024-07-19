#pragma once
#include"AbstractScene.h"
#include"SceneChangeEffect.h"
#include"MatchGameCommon.h"
#include<vector>
#include"ResultDrawBack.h"
#include"ResultString.h"
#include"ResultDrawHand.h"
#include"ResultKey.h"

class ResultScene final : public AbstractScene 
{
public:
	ResultScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	SceneChangeEffect m_sceneChange;
	ResultDrawBack m_drawBack;
	ResultString m_drawString;
	ResultDrawHand m_drawHand;
	ResultKey m_drawKey;

	std::vector<MatchField> m_field_list;

	//�֐�
	bool m_isIllegalFieldList(const std::vector<MatchField>& _field) const;

	//�ϐ��E�t���O
	bool m_illegal_field = false;	//�s���ȔՖʂ��ǂ����̃t���O

	bool m_mod_rule = false;		//MOD 5���[�����K�p����Ă��邩�̃t���O
	bool m_self_rule = false;		//�������[�����̗p����Ă��邩�̃t���O

	bool m_scene_change = false;	//���̃t���O�����������ɃV�[����߂�
	int m_scene_back_num = 0;		//���V�[���߂邩

	bool m_replay_save = false;		//���v���C��ۑ��ς݂��ǂ������ׂ�t���O
	bool m_replay_fail = false;		//���v���C��ۑ��Ɏ��s���������ׂ�t���O

	int m_select_field = 0;
};