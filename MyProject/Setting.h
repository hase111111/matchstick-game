#pragma once
#include "Singleton.h"
#include <map>
#include<string>

class Setting final : public Singleton<Setting> 
{
    Setting() {};
    friend Singleton< Setting >;

public:
    void loadSettingFile();
    void saveSettingFile(const int _vol, const bool _win, const bool _anime);

    int getSettingVol(const bool def_flag = false) const;
    bool getSettingFulWin(const bool def_flag = false) const;
    bool getSettingAnime(const bool def_flag = false) const;

    void setDefState();
private:
    int m_vol = 0;
    bool m_window_mode = false;
    bool m_anime_cut = false;

    const int m_DEF_VOL = 50;
    bool m_DEF_WIN = false;
    bool m_DEF_ANIME = false;
};