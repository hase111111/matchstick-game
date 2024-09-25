#pragma once
#include "Singleton.h"
#include <map>
#include<string>

class Sound final : public Singleton<Sound> {

public:
    Sound() {};
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