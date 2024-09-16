
#pragma once

#include <map>
#include <string>

#include "dxlib_assert.h"

namespace match_stick {

//! @brief SEを読み込むクラス．
class SoundEffectLoader final {
public:
    //! @brief SEを読み込む．
    //! 既に読み込んでいる場合は何もしない．
    //! ファイルが存在しない場合はアサートを発生させる．
    //! @param file_path ファイルパス．
    void loadSoundHandle(const std::string& file_path);

    //! @brief SEのハンドルを取得する．
    //! ファイルが読み込まれていない場合はアサートを発生させる．
    //! @param file_path ファイルパス．
    //! @return SEのハンドル．
    [[nodiscard]]
    inline int getSoundHandle(const std::string& file_path) const {
        ASSERT(isLoaded(file_path), "The sound effect is not loaded. File Path : " + file_path +
            ". Please call loadSoundHandle() before calling getSoundHandle().");

        return sound_handle_.at(file_path);
    }

    //! @brief 全てのSEの音量を変更する．
    //! 読み込んだSEの音量を変更し，今後読み込むSEの音量も変更する．
    //! @param volume 音量．
    void changeAllVolume(int volume);

    //! @brief SEの音量を取得する．
    //! @return SEの音量．
    [[nodiscard]]
    inline int getVolumePercent() const {
        return volume_percent_;
    }

private:
    [[nodiscard]]
    inline bool isLoaded(const std::string& file_path) const {
        return sound_handle_.contains(file_path);
    }

    std::map<std::string, int> sound_handle_;  //!< SEを格納する配列．キーはファイルパス．

    int volume_percent_{ 100 };  //!< SEの音量．
};

}  // namespace match_stick
