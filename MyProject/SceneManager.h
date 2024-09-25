#pragma once
#include<stack>
#include<memory>
#include"SceneChangeListenerInterface.h"

class SceneManger final : public SceneChangeListenerInterface{
public:
	SceneManger();
	~SceneManger() = default;

	bool updateTopScene();
	void drawTopScene() const;

	void addNewScene(const enumScene _sceneName, const Parameter& parameter) override;
	void deleteNowScene(const Parameter& parameter,int _how_many = 1) override;
	void deleteAllScene() override;
	void sceneChangeExecute();
private:
	std::stack<std::unique_ptr<AbstractScene>> m_uniqueSceneStack;
	const enumScene m_first_scene;

	enumScene m_scene_name;
	Parameter m_tempParam;
	int m_scenechange_command;
	int m_how_many_scene;
	void m_addNewScene(const enumScene _scene_name, const Parameter& _parameter);
};