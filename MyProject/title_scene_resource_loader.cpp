
#include "title_scene_resource_loader.h"

#include <format>

#include <magic_enum.hpp>

#include "dxlib_assert.h"
#include "language_record.h"

namespace match_stick {

TitleSceneResourceLoader::TitleSceneResourceLoader(
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

void TitleSceneResourceLoader::loadImage() {
    // 画像のロード
    image_loader_ptr_->loadImageHandle("data/img/title_back.png");
    image_loader_ptr_->loadImageHandle("data/img/icon_mouse.png");
    image_loader_ptr_->loadImageHandle("data/img/icon_keyboard.png");

    constexpr int hand_image_num = 6;
    for (unsigned int i = 0; i < hand_image_num; ++i) {
        image_loader_ptr_->loadImageHandle(std::format("data/img/hand/{}_hand.png", i));
    }

    // フォントのロード
    for (const auto& country : magic_enum::enum_values<LanguageRecord::Country>()) {
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font64.dft");
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font32.dft");
        font_loader_ptr_->loadFontHandle(country, "data/font/azuki_font20.dft");
    }

    // サウンドのロード
    sound_effect_loader_ptr_->loadSoundHandle("data/sound/op.mp3");
}

}  // namespace match_stick
