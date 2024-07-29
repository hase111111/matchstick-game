//#pragma once
//#include "AbstractScene.h"
//#include "SceneChangeEffect.h"
//#include "MenuDrawBack.h"
//#include "MenuBox.h"
//
//class MenuScene : public AbstractScene {
//public:
//	MenuScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);
//
//	bool update() override;
//	void draw() const override;
//	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;
//
//private:
//	//クラス
//	SceneChangeEffect m_scene_change_effect;
//	MenuDrawBack m_draw_back;
//	MenuBox m_box;
//
//	//シーンチェンジ用の変数
//	bool m_scene_change_flag = false;
//	enumScene m_which_scene = enumScene::title;
//	Parameter m_param;
//};
