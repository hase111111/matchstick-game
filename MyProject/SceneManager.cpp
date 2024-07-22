
#include"SceneManager.h"

#include "dxlib_assert.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "ResultScene.h"
#include "RuleScene.h"
#include "DebugScene.h"
#include "ReplayScene.h"

const int ADD_SCENE = 1;
const int BACK_SCENE = 2;
const int DELETE_ALL_SCENE = 3;
const int NO_COMMAND = -1;

SceneManger::SceneManger() :
    m_first_scene(enumScene::title),
    m_scenechange_command(NO_COMMAND),
    m_scene_name(enumScene::title),
    m_how_many_scene(0)
{
    //一番最初のシーンを追加
    Parameter p;
    m_addNewScene(m_first_scene, p);
}

bool SceneManger::updateTopScene()
{
    if (m_uniqueSceneStack.empty() == true) {
        ASSERT(false, "シーンが存在していないため、一番上のシーンを更新できません");
    }

    //トップのシーンを更新する。falseが返ってきたらソフトを終了する
    return m_uniqueSceneStack.top()->update();
}

void SceneManger::drawTopScene() const
{
    if (m_uniqueSceneStack.empty() == true) {
        ASSERT(false, "シーンが存在していないため、一番上のシーンを描画できません");
    }

    m_uniqueSceneStack.top()->draw();
}


void SceneManger::addNewScene(const enumScene _sceneName, const Parameter& parameter)
{
    //シーン追加の命令を出す
    m_scenechange_command = ADD_SCENE;
    m_scene_name = _sceneName;
    m_tempParam = parameter;
}

void SceneManger::deleteNowScene(const Parameter& parameter, int _how_many)
{
    //シーン削除の命令を出す
    m_scenechange_command = BACK_SCENE;
    m_tempParam = parameter;
    m_how_many_scene = _how_many;
}

void SceneManger::deleteAllScene()
{
    //シーン削除の命令を出す
    m_scenechange_command = DELETE_ALL_SCENE;
}


void SceneManger::sceneChangeExecute()
{
    if (m_scenechange_command == NO_COMMAND) {
        //何もしない
    }
    else if (m_scenechange_command == ADD_SCENE) //シーン追加命令の時
    {
        //シーン追加
        m_addNewScene(m_scene_name, m_tempParam);

        //命令をリセットする
        m_scenechange_command = NO_COMMAND;
        m_tempParam.resetParam();
    }
    else if (m_scenechange_command == BACK_SCENE) //シーン削除命令の時
    {
        //シーンを削除
        int cnt = (m_how_many_scene > 1) ? m_how_many_scene : 1;

        for (int i = 0; i < cnt; i++)
        {
            if (m_uniqueSceneStack.empty() == false) {
                m_uniqueSceneStack.pop();
            }
        }

        //シーンが存在しないなら最初のシーンを追加
        if (m_uniqueSceneStack.empty() == true) {
            Parameter p;
            m_addNewScene(m_first_scene, p);
        }

        //新たなトップシーンにパラメータを渡す
        if (m_uniqueSceneStack.empty() == true) {
            ASSERT(false, "シーンが存在していないため、パラメータを渡すことができません");
        }

        m_uniqueSceneStack.top()->receiveParameterInCaseOfDeleteScene(m_tempParam);

        //命令をリセットする
        m_scenechange_command = NO_COMMAND;

        //パラメータをリセットする
        m_tempParam.resetParam();
    }
    else if (m_scenechange_command == DELETE_ALL_SCENE) {
        //全シーン削除命令の時

        //全シーンを削除
        while (m_uniqueSceneStack.empty() == false) {
            m_uniqueSceneStack.pop();
        }

        //最初のシーンを追加
        Parameter p;
        m_addNewScene(m_first_scene, p);

        //命令をリセットする
        m_scenechange_command = NO_COMMAND;
        m_tempParam.resetParam();
    }
    else {
        std::string err = "シーン変更クラスでエラーが発生しました。\n不明なコマンド...";
        err += std::to_string(m_scenechange_command);
        ASSERT(false, err.c_str());
    }

}

void SceneManger::m_addNewScene(const enumScene _scene_name, const Parameter& _parameter)
{
    switch (_scene_name)
    {
        case enumScene::title:
            m_uniqueSceneStack.push(std::make_unique<TitleScene>(this, _parameter));
            break;

        case enumScene::game:
            m_uniqueSceneStack.push(std::make_unique<GameScene>(this, _parameter));
            break;

        case enumScene::menu:
            m_uniqueSceneStack.push(std::make_unique<MenuScene>(this, _parameter));
            break;

        case enumScene::result:
            m_uniqueSceneStack.push(std::make_unique<ResultScene>(this, _parameter));
            break;

        case enumScene::rule:
            m_uniqueSceneStack.push(std::make_unique<RuleScene>(this, _parameter));
            break;

        case enumScene::debug:
            m_uniqueSceneStack.push(std::make_unique<DebugScene>(this, _parameter));
            break;

        case enumScene::replay:
            m_uniqueSceneStack.push(std::make_unique<ReplayScene>(this, _parameter));
            break;

        default:
            ASSERT_MUST_NOT_REACH_HERE();
            break;
    }
}
