
#pragma once

#include <map>
#include <string>

#include "singleton.h"

class Sound final : public Singleton<Sound> {
public:
    Sound() = default;
    ~Sound() = default;

    int myLoadSound(std::string _path);
    void startBGM(std::string _path);
    void stopBGM();
    void changeVolume(const int percent);

private:
    std::map<std::string, int> m_soundeffect;

    std::map<std::string, int> m_bgm;
    std::string m_playbgm = "";

    int m_percent = 100;
};
