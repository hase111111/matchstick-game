
#pragma once

#include "bgm_player.h"
#include "font_loader.h"
#include "image_loader.h"
#include "sound_effect_loader.h"

namespace match_stick {

class DxLibResourceLoader final {
    using Country = LanguageRecord::Country;
public:
    DxLibResourceLoader() = default;
    ~DxLibResourceLoader() = default;

    // FontLoader
    [[nodiscard]]
    inline int getFontHandle(Country country, const std::string& file_path) const {
        return font_loader_.getFontHandle(country, file_path);
    }

    inline void loadFontHandle(Country country, const std::string& file_path) {
        font_loader_.loadFontHandle(country, file_path);
    }

    // ImageLoader
    [[nodiscard]]
    inline int getImageHandle(const std::string& file_path) const {
        return image_loader_.getImageHandle(file_path);
    }

    inline void loadImageHandle(const std::string& file_path) {
        image_loader_.loadImageHandle(file_path);
    }

    // SoundEffectLoader
    [[nodiscard]]
    inline int getSoundHandle(const std::string& file_path) const {
        return sound_effect_loader_.getSoundHandle(file_path);
    }

    inline void loadSoundHandle(const std::string& file_path) {
        sound_effect_loader_.loadSoundHandle(file_path);
    }

    inline void changeAllSoundVolume(const int volume) {
        sound_effect_loader_.changeAllSoundVolume(volume);
    }

private:
    BgmPlayer bgm_player_;
    FontLoader font_loader_;
    ImageLoader image_loader_;
    SoundEffectLoader sound_effect_loader_;
};

} // namespace match_stick
