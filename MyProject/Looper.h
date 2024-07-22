
#pragma once

#include <memory>

#include "fps.h"
#include "SceneManager.h"

class Looper {
public:
    Looper();
    ~Looper() = default;

    bool loop();

private:
    SceneManger m_sceneMgr;
    Fps m_fps;
};
