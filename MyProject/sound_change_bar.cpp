
#include "sound_change_bar.h"

#include <format>
#include <string>

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"

namespace {

constexpr int kBoxWidth = ::match_stick::GameConst::kResolutionX * 2 / 3;
constexpr int kBoxHeight = ::match_stick::GameConst::kResolutionY * 7 / 18;
constexpr int kBoxDiff = ::match_stick::GameConst::kResolutionY / 128;

constexpr int kBarWidth = static_cast<int>((kBoxWidth - kBoxDiff * 2) * 0.6);
constexpr int kBarHeight = ::match_stick::GameConst::kResolutionY / 128;

constexpr int kBarPosY = ::match_stick::GameConst::kResolutionY / 6;

}  // namespace

namespace match_stick {

SoundChangeBar::SoundChangeBar(
    const std::shared_ptr<const LanguageRecord>& language_record_ptr,
    const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr,
    int x, int y) :
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr),
    font32_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font32.dft")),
    center_x_(x),
    center_y_(y) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
}


bool SoundChangeBar::update() {
    return true;
}

void SoundChangeBar::draw() const {
    DrawBox(
        center_x_ - kBoxWidth / 2,
        center_y_ - kBoxHeight / 2,
        center_x_ + kBoxWidth / 2,
        center_y_ + kBoxHeight / 2,
        GameConst::kDarkGrayColor,
        TRUE);

    DrawBox(
        center_x_ - kBoxWidth / 2 + kBoxDiff,
        center_y_ - kBoxHeight / 2 + kBoxDiff,
        center_x_ + kBoxWidth / 2 - kBoxDiff,
        center_y_ + kBoxHeight / 2 - kBoxDiff,
        GameConst::kWhiteColor,
        TRUE);

    drawBar();

    // 文字を描画
    const std::string bgm_str = std::format("BGM:{}", dxlib_resource_loader_ptr_->getBGMVolumePercent());
    const int bgm_str_width =
        GetDrawStringWidthToHandle(bgm_str.c_str(), static_cast<int>(bgm_str.size()), font32_handle_);
    const int str_height = GetFontSizeToHandle(font32_handle_);

    DrawFormatStringToHandle(center_x_ - bgm_str_width / 2, center_y_ - kBoxHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, bgm_str.c_str());

    const std::string se_str = std::format("SE:{}", dxlib_resource_loader_ptr_->getSEVolumePercent());
    const int se_str_width =
        GetDrawStringWidthToHandle(se_str.c_str(), static_cast<int>(se_str.size()), font32_handle_);

    DrawFormatStringToHandle(center_x_ - se_str_width / 2, center_y_ - kBoxHeight / 2 + kBarPosY + str_height * 3 / 4,
        GameConst::kBlackColor, font32_handle_, se_str.c_str());

    // +5, +1, +5, +1 の文字を描画
    const int plus_width = GetDrawStringWidthToHandle("+1", 3, font32_handle_);

    DrawFormatStringToHandle(
        center_x_ - kBoxWidth / 2 + plus_width * 1 / 2, center_y_ - kBoxHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, "+5");

    DrawFormatStringToHandle(
        center_x_ - kBoxWidth / 2 + plus_width * 4 / 2, center_y_ - kBoxHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, "+1");

    DrawFormatStringToHandle(
        center_x_ + kBoxWidth / 2 - plus_width * 3 / 2, center_y_ - kBoxHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, "+5");

    DrawFormatStringToHandle(
        center_x_ + kBoxWidth / 2 - plus_width * 6 / 2, center_y_ - kBoxHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, "+1");
}

bool SoundChangeBar::isHovered(int mouse_x, int mouse_y) const {
    return false;
}

void SoundChangeBar::initHoverState(bool is_hovered) {}

void SoundChangeBar::callbackWhenClicked() {}

void SoundChangeBar::callbackWhenHoverStarted() {}

void SoundChangeBar::callbackWhenHoverEnded() {}

void SoundChangeBar::drawBar() const {
    // BGM 音量バー
    const int bar_left_x = center_x_ - kBarWidth / 2;
    const int bar_right_x = center_x_ + kBarWidth / 2;
    const int bgm_upper_y = center_y_ - kBoxHeight / 2 - kBarHeight / 2 + kBarPosY;
    const int bgm_lower_y = center_y_ - kBoxHeight / 2 + kBarHeight / 2 + kBarPosY;

    DrawBox(bar_left_x, bgm_upper_y, bar_right_x, bgm_lower_y, GameConst::kBlackColor, TRUE);

    DrawBox(
        bar_left_x - kBarHeight / 2,
        (bgm_upper_y + bgm_lower_y) / 2 - kBarHeight * 3,
        bar_left_x + kBarHeight / 2,
        (bgm_upper_y + bgm_lower_y) / 2 + kBarHeight * 3,
        GameConst::kBlackColor, TRUE);

    DrawBox(
        bar_right_x - kBarHeight / 2,
        (bgm_upper_y + bgm_lower_y) / 2 - kBarHeight * 3,
        bar_right_x + kBarHeight / 2,
        (bgm_upper_y + bgm_lower_y) / 2 + kBarHeight * 3,
        GameConst::kBlackColor, TRUE);

    // BGM の現在値の位置を描画
    const int bgm_volume = dxlib_resource_loader_ptr_->getBGMVolumePercent();
    const int bgm_x = bar_left_x + kBarWidth * (100 - bgm_volume) / 100;

    DrawTriangleAA(
        static_cast<float>(bgm_x), static_cast<float>(bgm_upper_y),
        static_cast<float>(bgm_x) - triangle_width_ / 2.f, static_cast<float>(bgm_upper_y) - triangle_width_,
        static_cast<float>(bgm_x) + triangle_width_ / 2.f, static_cast<float>(bgm_upper_y) - triangle_width_,
        GameConst::kBlackColor, TRUE);

    // SE 音量バー
    const int se_upper_y = center_y_ - kBoxHeight / 2 - kBarHeight / 2 + kBarPosY * 2;
    const int se_lower_y = center_y_ - kBoxHeight / 2 + kBarHeight / 2 + kBarPosY * 2;

    DrawBox(bar_left_x, se_upper_y, bar_right_x, se_lower_y, GameConst::kBlackColor, TRUE);

    DrawBox(
        bar_left_x - kBarHeight,
        (se_upper_y + se_lower_y) / 2 - kBarHeight * 3,
        bar_left_x,
        (se_upper_y + se_lower_y) / 2 + kBarHeight * 3,
        GameConst::kBlackColor, TRUE);

    DrawBox(
        bar_right_x,
        (se_upper_y + se_lower_y) / 2 - kBarHeight * 3,
        bar_right_x + kBarHeight,
        (se_upper_y + se_lower_y) / 2 + kBarHeight * 3,
        GameConst::kBlackColor, TRUE);

    // SE の現在値の位置を描画
    const int se_volume = dxlib_resource_loader_ptr_->getSEVolumePercent();
    const int se_x = bar_left_x + kBarWidth * (100 - se_volume) / 100;

    DrawTriangleAA(
        static_cast<float>(se_x), static_cast<float>(se_upper_y),
        static_cast<float>(se_x) - triangle_width_ / 2.f, static_cast<float>(se_upper_y) - triangle_width_,
        static_cast<float>(se_x) + triangle_width_ / 2.f, static_cast<float>(se_upper_y) - triangle_width_,
        GameConst::kBlackColor, TRUE);
}

}  // namespace match_stick
