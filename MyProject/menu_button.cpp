
#include "menu_button.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"
#include "math_const.h"

namespace {

constexpr int kButtonWidth = match_stick::GameConst::kResolutionX * 100 / 369;
constexpr int kButtonHeight = match_stick::GameConst::kResolutionY * 100 / 257;

constexpr int kLargeButtonWidth = match_stick::GameConst::kResolutionX * 9 / 16;

}  // namespace

namespace match_stick {

MenuButton::MenuButton(
    const std::shared_ptr<const LanguageRecord>& language_record,
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader,
    int center_x, int center_y,
    const std::string& icon_path,
    const std::string& text_key,
    const std::function<void()>& callback_when_clicked,
    const bool is_large_button) :
    font_handle_(dxlib_resource_loader->getFontHandle(language_record->getCurrentCountry(),
        is_large_button ? "data/font/azuki_font48.dft" : "data/font/azuki_font32.dft")),
    icon_image_handle_(dxlib_resource_loader->getImageHandle(icon_path)),
    click_sound_handle_(dxlib_resource_loader->getSoundHandle("data/sound/selecting2.mp3")),
    hover_sound_handle_(dxlib_resource_loader->getSoundHandle("data/sound/selecting3.mp3")),
    center_x_(center_x),
    center_y_(center_y),
    width_(is_large_button ? kLargeButtonWidth : kButtonWidth),
    height_(kButtonHeight),
    button_base_color_(GameConst::kBrightWhiteColor),
    button_hovered_color_(GameConst::kLightGrayColor),
    button_frame_color_(GameConst::kDarkGrayColor),
    button_text_color_(GameConst::kBlackColor),
    text_(language_record->getValue(text_key)),
    callback_when_clicked_(callback_when_clicked),
    is_large_button_(is_large_button) {
    // nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(language_record);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader);
}

bool MenuButton::isHovered(const int mouse_x, const int mouse_y) const {
    return (center_x_ - width_ / 2 <= mouse_x && mouse_x <= center_x_ + width_ / 2 &&
            center_y_ - height_ / 2 <= mouse_y && mouse_y <= center_y_ + height_ / 2);
}

void MenuButton::initHoverState(bool is_hovered) {
    is_hovered_ = is_hovered;
}

void MenuButton::callbackWhenClicked() {
    DxLib::PlaySoundMem(click_sound_handle_, DX_PLAYTYPE_BACK);

    callback_when_clicked_();
}

void MenuButton::callbackWhenHoverStarted() {
    DxLib::PlaySoundMem(hover_sound_handle_, DX_PLAYTYPE_BACK);

    is_hovered_ = true;

    icon_rotation_ = MathConst<double>::kPi * 2.0;
}

void MenuButton::callbackWhenHoverEnded() {
    is_hovered_ = false;
}

bool MenuButton::update() {
    if (icon_rotation_ > 0) {
        icon_rotation_ -= MathConst<double>::kPi * 0.16;
    } else {
        icon_rotation_ = 0.0;
    }

    return true;
}

void MenuButton::draw() const {
    // ボタンの描画
    DxLib::DrawBox(
        center_x_ - width_ / 2, center_y_ - height_ / 2,
        center_x_ + width_ / 2, center_y_ + height_ / 2,
        button_frame_color_, TRUE);

    DxLib::DrawBox(
        center_x_ - width_ / 2 + button_thickness_, center_y_ - height_ / 2 + button_thickness_,
        center_x_ + width_ / 2 - button_thickness_, center_y_ + height_ / 2 - button_thickness_,
        is_hovered_ ? button_hovered_color_ : button_base_color_, TRUE);

    if (is_large_button_) {
        // アイコンの描画
        DxLib::DrawRotaGraph(
            center_x_ - width_ * 1 / 3, center_y_,
            1.0, icon_rotation_, icon_image_handle_, TRUE);

        // テキストの描画
        const int text_width = DxLib::GetDrawStringWidthToHandle(
            text_.c_str(), static_cast<int>(text_.size()), font_handle_);
        const int text_height = DxLib::GetFontSizeToHandle(font_handle_);

        DxLib::DrawStringToHandle(
            center_x_ + width_ / 3 - text_width,
            center_y_ - height_ / 10 - text_height / 2,
            text_.c_str(), button_text_color_, font_handle_);
    } else {
        // アイコンの描画
        DxLib::DrawRotaGraph(
            center_x_, center_y_ + height_ / 6,
            0.8, icon_rotation_, icon_image_handle_, TRUE);

        // テキストの描画
        const int text_width = DxLib::GetDrawStringWidthToHandle(
            text_.c_str(), static_cast<int>(text_.size()), font_handle_);
        const int text_height = DxLib::GetFontSizeToHandle(font_handle_);

        DxLib::DrawStringToHandle(
            center_x_ - text_width / 2,
            center_y_ - height_ * 3 / 10 - text_height / 2,
            text_.c_str(), button_text_color_, font_handle_);
    }
}


}  // namespace match_stick
