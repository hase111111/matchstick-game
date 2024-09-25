#pragma once
#include "AbstractScene.h"
#include "SceneChangeEffect.h"
#include"RulePage.h"

class RuleScene : public AbstractScene 
{
public:
	RuleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	SceneChangeEffect m_scene_change;
	RulePage m_rule;

	int m_page;
	int m_page_MAX;
	bool m_scene_change_flag = false;

	//�`��p�̃t�H���g
	int m_font;

	//�`��p�̉摜�n���h��
	int m_image;

	//�T�E���h�n���h��
	int m_sound;

	//�N���X����̂��邭�Ȃ��Ă����̂Ŋ֐�
	void m_drawArrow() const;
	void m_drawBack() const;
};