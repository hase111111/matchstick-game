
#include "menu_scene_resource_loader.h"

#include <format>

#include <magic_enum.hpp>

#include "dxlib_assert.h"
#include "language_record.h"

namespace match_stick {

MenuSceneResourceLoader::MenuSceneResourceLoader(
    const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr) {
    // NULL チェック
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr_);
}

void MenuSceneResourceLoader::loadImage() {
    // 画像のロード
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_mouse.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_keyboard.png");

    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_game.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_rule.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_setting.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_replay.png");
    dxlib_resource_loader_ptr_->loadImageHandle("data/img/icon_language.png");

    // フォントのロード
    for (const auto& country : magic_enum::enum_values<LanguageRecord::Country>()) {
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font20.dft");
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font24.dft");
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font32.dft");
        dxlib_resource_loader_ptr_->loadFontHandle(country, "data/font/azuki_font48.dft");
    }

    // サウンドのロード
    dxlib_resource_loader_ptr_->loadSoundHandle("data/sound/selecting2.mp3");
    dxlib_resource_loader_ptr_->loadSoundHandle("data/sound/selecting3.mp3");
}

}  // namespace match_stick
