
#include "bgm_player.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace homerun
{

void BgmPlayer::Load(const std::string& bgm_file)
{
    if (bgm_handle_.count(bgm_file) != 0)
    {
        return;
    }

    const int bgm_handle = LoadSoundMem(bgm_file.c_str());

    ASSERT(bgm_handle >= 0, "Failed to load BGM. File Path : " + bgm_file);

    bgm_handle_[bgm_file] = bgm_handle;

    // 音量を変更する．
    ChangeVolumeSoundMem(255 * volume_percent_ / 100, bgm_handle_[bgm_file]);
}

void BgmPlayer::Play(const std::string& bgm_file)
{
    if (current_bgm_.has_value())
    {
        if (current_bgm_.value() == bgm_file)
        {
            // すでに再生中のBGMと同じBGMを再生しようとした場合は何もしない．
            return;
        }

        // すでに再生中のBGMを停止する．
        Stop();
    }

    PlaySoundMem(bgm_handle_[bgm_file], DX_PLAYTYPE_LOOP);
    current_bgm_ = bgm_file;
}

void BgmPlayer::LoadAndPlay(const std::string& bgm_file)
{
    Load(bgm_file);
    Play(bgm_file);
}

void BgmPlayer::Stop()
{
    if (current_bgm_.has_value())
    {
        StopSoundMem(bgm_handle_[current_bgm_.value()]);

        current_bgm_.reset();
    }
}

void BgmPlayer::ChangeVolume(const int volume)
{
    ASSERT(volume >= 0 && volume <= 100, "Volume must be in the range of 0 to 100.");

    volume_percent_ = volume;

    if (current_bgm_.has_value())
    {
        ChangeVolumeSoundMem(255 * volume_percent_ / 100, bgm_handle_[current_bgm_.value()]);
    }
}

}  // namespace homerun
