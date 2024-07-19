#pragma once
#include"Parameter.h"
#include"SceneChangeListenerInterface.h"

class SceneChangeListenerInterface;

class AbstractScene
{
protected:
    SceneChangeListenerInterface* mp_listenerInterface;
public:
    AbstractScene(SceneChangeListenerInterface* pScli, const Parameter& parameter);
    virtual ~AbstractScene() = default;
    virtual bool update()     = 0;
    virtual void draw() const = 0;
    virtual void receiveParameterInCaseOfDeleteScene(const Parameter& parameter) = 0;
};