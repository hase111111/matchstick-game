#pragma once
#include"AbstractScene.h"

class DebugScene final : public AbstractScene
{
public:
	DebugScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);

	bool update() override;
	void draw() const override;
	void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) override;

private:

};