
#include "sound_effect_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

int SoundEffectLoader::loadAndGetSoundHandle(const std::string& file_path) {
    if (sound_handle_.count(file_path) != 0) {
        return sound_handle_[file_path];
    }

    const int sound_handle = LoadSoundMem(file_path.c_str());

    ASSERT(sound_handle >= 0, "Failed to load sound effect. File Path : " + file_path);

    sound_handle_[file_path] = sound_handle;

    // 音量を変更する．
    ChangeVolumeSoundMem(255 * volume_percent_ / 100, sound_handle_[file_path]);

    return sound_handle_[file_path];
}

void SoundEffectLoader::changeAllSoundVolume(const int volume) {
    ASSERT(volume >= 0 && volume <= 100, "Volume must be between 0 and 100. Volume : " + std::to_string(volume));

    volume_percent_ = volume;

    for (auto& sound : sound_handle_) {
        ChangeVolumeSoundMem(255 * volume_percent_ / 100, sound.second);
    }
}

}  // namespace match_stick
