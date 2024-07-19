#pragma once
#include"AbstractScene.h"
#include"TitleAnime.h"
#include"SceneChangeEffect.h"
#include<memory>

class TitleScene final : public AbstractScene {
public:
	TitleScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:
	TitleAnime m_anime;
	SceneChangeEffect m_change;
	bool m_scene_change;

	//サウンドのハンドル
	int m_sound = 0;
};