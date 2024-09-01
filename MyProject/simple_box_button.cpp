
#include "simple_box_button.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"

namespace match_stick {

SimpleBoxButton::SimpleBoxButton(
    const std::shared_ptr<const LanguageRecord>& language_record,
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader,
    const int center_x, const int center_y, const int width, const int height,
    const std::string& text_key,
    const std::string& font_name,
    const std::function<void()>& callback_when_clicked) :
    font_handle_(dxlib_resource_loader->getFontHandle(language_record->getCurrentCountry(), font_name)),
    click_sound_handle_(dxlib_resource_loader->getSoundHandle("data/sound/selecting2.mp3")),
    hover_sound_handle_(dxlib_resource_loader->getSoundHandle("data/sound/selecting3.mp3")),
    center_x_(center_x),
    center_y_(center_y),
    width_(width),
    height_(height),
    text_(language_record->getValue(text_key)),
    callback_when_clicked_(callback_when_clicked) {
    // nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(language_record);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader);

    // 色を設定
    button_base_color_ = GameConst::kWhiteColor;
    button_hovered_color_ = GameConst::kGrayColor;
    button_frame_color_ = GameConst::kBlackColor;
}

bool SimpleBoxButton::isHovered(const int mouse_x, const int mouse_y) const {
    return (center_x_ - width_ / 2 <= mouse_x && mouse_x <= center_x_ + width_ / 2 &&
            center_y_ - height_ / 2 <= mouse_y && mouse_y <= center_y_ + height_ / 2);
}

void SimpleBoxButton::initHoverState(const bool is_hovered) {
    is_hovered_ = is_hovered;
}

void SimpleBoxButton::callbackWhenClicked() {
    DxLib::PlaySoundMem(click_sound_handle_, DX_PLAYTYPE_BACK);

    callback_when_clicked_();
}

void SimpleBoxButton::callbackWhenHoverStarted() {
    DxLib::PlaySoundMem(hover_sound_handle_, DX_PLAYTYPE_BACK);

    is_hovered_ = true;
}

void SimpleBoxButton::callbackWhenHoverEnded() {
    is_hovered_ = false;
}

void SimpleBoxButton::draw() const {
    // ボタンの色を設定
    const unsigned int button_color = is_hovered_ ? button_hovered_color_ : button_base_color_;

    // ボタンの枠を描画
    DxLib::DrawBox(center_x_ - width_ / 2, center_y_ - height_ / 2,
                   center_x_ + width_ / 2, center_y_ + height_ / 2,
                   button_frame_color_, TRUE);

    // ボタンの中身を描画
    DxLib::DrawBox(center_x_ - width_ / 2 + button_thickness_, center_y_ - height_ / 2 + button_thickness_,
                   center_x_ + width_ / 2 - button_thickness_, center_y_ + height_ / 2 - button_thickness_,
                   button_color, TRUE);

    // テキストを描画
    const int text_width = DxLib::GetDrawStringWidthToHandle(
        text_.c_str(), static_cast<int>(text_.size()), font_handle_);
    const int text_height = DxLib::GetFontSizeToHandle(font_handle_);

    DxLib::DrawStringToHandle(center_x_ - text_width / 2, center_y_ - text_height / 2,
                              text_.c_str(), button_frame_color_, font_handle_);
}

}  // namespace match_stick
