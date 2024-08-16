
#pragma once

#include <map>
#include <string>

#include "dxlib_assert.h"

namespace match_stick {

//! @brief SEを読み込むクラス．
class SoundEffectLoader final {
public:
    void loadSoundHandle(const std::string& file_path);

    [[nodiscard]]
    int loadAndGetSoundHandle(const std::string& file_path);

    [[nodiscard]]
    inline int getSoundHandle(const std::string& file_path) const {
        ASSERT(sound_handle_.count(file_path) != 0, "The sound effect is not loaded. File is " + file_path);
        return sound_handle_.at(file_path);
    }

    [[nodiscard]]
    inline bool isSoundLoaded(const std::string& file_path) const {
        return sound_handle_.count(file_path) != 0;
    }

    void changeAllSoundVolume(int volume);

private:
    std::map<std::string, int> sound_handle_;  //!< SEを格納する配列．キーはファイルパス．

    int volume_percent_{ 100 };  //!< SEの音量．
};

}  // namespace match_stick
