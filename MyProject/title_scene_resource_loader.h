
#pragma once

#include <memory>

#include "font_loader.h"
#include "image_loader.h"
#include "sound_effect_loader.h"

namespace match_stick {

class TitleSceneResourceLoader final {
public:
    TitleSceneResourceLoader(const std::shared_ptr<FontLoader>& font_loader_ptr,
                             const std::shared_ptr<ImageLoader>& image_loader_ptr,
                             const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);
    ~TitleSceneResourceLoader() = default;

    void loadImage();

private:
    const std::shared_ptr<FontLoader> font_loader_ptr_;
    const std::shared_ptr<ImageLoader> image_loader_ptr_;
    const std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr_;
};

}  // namespace match_stick
