//#pragma once
//#include "AbstractScene.h"
//#include "SceneChangeEffect.h"
//#include"RulePage.h"
//
//class RuleScene : public AbstractScene 
//{
//public:
//	RuleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);
//
//	bool update() override;
//	void draw() const override;
//	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;
//
//private:
//	SceneChangeEffect m_scene_change;
//	RulePage m_rule;
//
//	int m_page;
//	int m_page_MAX;
//	bool m_scene_change_flag = false;
//
//	//描画用のフォント
//	int m_font;
//
//	//描画用の画像ハンドル
//	int m_image;
//
//	//サウンドハンドル
//	int m_sound;
//
//	//クラスつくるのだるくなってきたので関数
//	void m_drawArrow() const;
//	void m_drawBack() const;
//};