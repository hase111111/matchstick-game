
#include "bgm_player.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

void BgmPlayer::loadBGM(const std::string& bgm_file) {
    if (isLoaded(bgm_file)) {
        return;
    }

    const int bgm_handle = LoadSoundMem(bgm_file.c_str());

    ASSERT(bgm_handle >= 0, "Failed to load BGM. File Path : " + bgm_file);

    bgm_handle_[bgm_file] = bgm_handle;

    // 音量を変更する．
    ChangeVolumeSoundMem(255 * volume_percent_ / 100, bgm_handle_[bgm_file]);
}

void BgmPlayer::playBGM(const std::string& bgm_file) {
    ASSERT(isLoaded(bgm_file), "BGM is not loaded. File Path : " + bgm_file +
        ". Please call loadBGM() before calling playBGM().");

    if (current_bgm_.has_value()) {
        if (current_bgm_.value() == bgm_file) {
            // すでに再生中のBGMと同じBGMを再生しようとした場合は何もしない．
            return;
        }

        // すでに再生中のBGMを停止する．
        stopBGM();
    }

    PlaySoundMem(bgm_handle_[bgm_file], DX_PLAYTYPE_LOOP);
    current_bgm_ = bgm_file;
}

void BgmPlayer::stopBGM() {
    if (current_bgm_.has_value()) {
        StopSoundMem(bgm_handle_[current_bgm_.value()]);

        current_bgm_.reset();
    }
}

void BgmPlayer::changeAllVolume(const int volume) {
    ASSERT(0 <= volume && volume <= 100, "Volume must be in the range of 0 to 100.");

    volume_percent_ = volume;

    if (current_bgm_.has_value()) {
        ChangeVolumeSoundMem(255 * volume_percent_ / 100, bgm_handle_[current_bgm_.value()]);
    }
}

}  // namespace match_stick
