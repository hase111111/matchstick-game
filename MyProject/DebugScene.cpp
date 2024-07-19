#include "DebugScene.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "MatchGameCommon.h"
#include <vector>
#include "Setting.h"

DebugScene::DebugScene(SceneChangeListenerInterface* pScli, const Parameter& parameter) : AbstractScene(pScli, parameter)
{
    Setting::getIns()->saveSettingFile(43, true, true);
}

bool DebugScene::update()
{
    return true;
}

void DebugScene::draw() const
{
}

void DebugScene::receiveParameterInCaseOfDeleteScene(const Parameter& parameter)
{
}
