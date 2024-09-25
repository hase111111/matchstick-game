#pragma once
#include"SceneEnum.h"
#include"Parameter.h"
#include"AbstractScene.h"

class SceneChangeListenerInterface {
public:
	SceneChangeListenerInterface() = default;
	virtual ~SceneChangeListenerInterface() = default;

	virtual void addNewScene(const enumScene _sceneName, const Parameter& parameter) = 0;
	virtual void deleteNowScene(const Parameter& parameter, int _how_many = 1) = 0;
	virtual void deleteAllScene() = 0;
};