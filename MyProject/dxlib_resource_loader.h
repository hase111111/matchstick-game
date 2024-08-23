
#pragma once

#include "bgm_player.h"
#include "font_loader.h"
#include "image_loader.h"
#include "sound_effect_loader.h"

namespace match_stick {

class DxLibResourceLoader final {
public:
    DxLibResourceLoader() = default;
    ~DxLibResourceLoader() = default;

    void LoadResource() const;
    void UnloadResource() const;

private:
    BgmPlayer bgm_player_;
    FontLoader font_loader_;
    ImageLoader image_loader_;
    SoundEffectLoader sound_effect_loader_;
};

} // namespace match_stick
