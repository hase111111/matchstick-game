
#pragma once

#include <map>
#include <string>

namespace match_stick
{

//! @brief SEを読み込むクラス．
class SoundEffectLoader final
{
public:
    int LoadAndGetSoundHandle(const std::string& file_path);

    void ChangeAllSoundVolume(int volume);

private:
    std::map<std::string, int> sound_handle_;  //!< SEを格納する配列．キーはファイルパス．

    int volume_percent_{ 100 };  //!< SEの音量．
};

}  // namespace match_stick
