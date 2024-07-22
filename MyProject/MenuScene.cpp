
#include "MenuScene.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "Keyboard.h"

MenuScene::MenuScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
{
    m_scene_change_effect.init(3);
}

bool MenuScene::update()
{
    //背景の更新は常に行う
    m_draw_back.update();

    //シーンエフェクトの更新が終了してからメインの処理を行う
    if (m_scene_change_effect.update() == false)
    {
        //ゲーム終了の処理
        if (m_box.getGameEnd() == true)
        {
            //ゲーム終了ならばFALSEを返す
            return false;
        }

        //シーンチェンジ命令が出るかどうか
        if (m_box.update(m_which_scene, m_param) == true) {
            m_scene_change_flag = true;

            if (m_which_scene == enumScene::title) { m_scene_change_effect.init(2); }
            else { m_scene_change_effect.init(0); }

            return true;
        }

        //シーンチェンジ命令が出ているならば
        if (m_scene_change_flag == true)
        {
            if (m_which_scene == enumScene::title) {
                mp_listenerInterface->deleteNowScene(m_param);
            }
            else if (m_which_scene == enumScene::game) {
                mp_listenerInterface->addNewScene(enumScene::game, m_param);
            }
            else if (m_which_scene == enumScene::rule) {
                mp_listenerInterface->addNewScene(enumScene::rule, m_param);
            }
            else if (m_which_scene == enumScene::result) {
                mp_listenerInterface->addNewScene(enumScene::result, m_param);
            }
            else if (m_which_scene == enumScene::replay) {
                mp_listenerInterface->addNewScene(enumScene::replay, m_param);
            }
            else { ASSERT_MUST_NOT_REACH_HERE(); }
            return true;
        }
    }

    return true;
}

void MenuScene::draw() const
{
    //背景を描画
    m_draw_back.draw();

    //四角を描画
    m_box.draw();

    //シーンチェンジエフェクトを描画
    m_scene_change_effect.draw();
}

void MenuScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
    //シーンチェンジのエフェクトを再生する
    m_scene_change_effect.init(1);

    //シーンチェンジ用のフラグを戻す
    m_scene_change_flag = false;
    m_which_scene = enumScene::title;
    m_param.resetParam();
}