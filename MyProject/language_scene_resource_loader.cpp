
#include "language_scene_resource_loader.h"

#include <format>

#include <magic_enum.hpp>

#include "dxlib_assert.h"
#include "language_record.h"

namespace match_stick {

LanguageSceneResourceLoader::LanguageSceneResourceLoader(
    const std::shared_ptr<FontLoader>& font_loader_ptr,
    const std::shared_ptr<ImageLoader>& image_loader_ptr,
    const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    font_loader_ptr_(font_loader_ptr),
    image_loader_ptr_(image_loader_ptr),
    sound_effect_loader_ptr_(sound_effect_loader_ptr) {
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(image_loader_ptr);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr);

    ASSERT_NOT_NULL_PTR(font_loader_ptr_);
    ASSERT_NOT_NULL_PTR(image_loader_ptr_);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr_);
}

void LanguageSceneResourceLoader::loadImage() {
    // 画像のロード
    image_loader_ptr_->loadImageHandle("data/img/icon_mouse.png");
    image_loader_ptr_->loadImageHandle("data/img/icon_keyboard.png");
    image_loader_ptr_->loadImageHandle("data/img/icon_language.png");
    image_loader_ptr_->loadImageHandle("data/img/icon_checked.png");

    // フォントのロード
    for (const auto& country : magic_enum::enum_values<LanguageRecord::Country>()) {
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font20.dft");
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font24.dft");
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font32.dft");
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font48.dft");
    }

    // サウンドのロード
    sound_effect_loader_ptr_->loadSoundHandle("data/sound/selecting2.mp3");
    sound_effect_loader_ptr_->loadSoundHandle("data/sound/selecting3.mp3");
}

}  // namespace match_stick
