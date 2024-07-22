
#ifndef HOMERUN_SOUND_EFFECT_LOADER_H_
#define HOMERUN_SOUND_EFFECT_LOADER_H_

#include <map>
#include <string>

namespace homerun
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

}  // namespace homerun

#endif  // HOMERUN_SOUND_EFFECT_LOADER_H_
