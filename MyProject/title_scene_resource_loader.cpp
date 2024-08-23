
#include "title_scene_resource_loader.h"

#include <format>

#include <magic_enum.hpp>

#include "dxlib_assert.h"
#include "language_record.h"

namespace match_stick {

TitleSceneResourceLoader::TitleSceneResourceLoader(
    const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr) {
    // NULL チェック
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr_);
}

void TitleSceneResourceLoader::loadImage() {
    // 画像のロード
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/title_back.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_mouse.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_keyboard.png");

    constexpr int hand_image_num = 6;
    for (unsigned int i = 0; i < hand_image_num; ++i) {
        dxlib_resource_loader_ptr_->loadImageHandle(std::format("data/img/hand/{}_hand.png", i));
    }

    // フォントのロード
    for (const auto& country : magic_enum::enum_values<LanguageRecord::Country>()) {
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font64.dft");
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font32.dft");
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font20.dft");
    }

    // サウンドのロード
    dxlib_resource_loader_ptr_->loadSoundHandle("data/sound/op.mp3");
}

}  // namespace match_stick
