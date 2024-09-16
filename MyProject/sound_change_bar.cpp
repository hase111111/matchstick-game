
#include "sound_change_bar.h"

#include <format>
#include <string>

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"

namespace {

constexpr int kBarWidth = ::match_stick::GameConst::kResolutionX * 2 / 3;
constexpr int kBarHeight = ::match_stick::GameConst::kResolutionY / 3;
constexpr int kBarDiff = ::match_stick::GameConst::kResolutionY / 128;

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
        center_x_ - kBarWidth / 2,
        center_y_ - kBarHeight / 2,
        center_x_ + kBarWidth / 2,
        center_y_ + kBarHeight / 2,
        GameConst::kDarkGrayColor,
        TRUE);

    DrawBox(
        center_x_ - kBarWidth / 2 + kBarDiff,
        center_y_ - kBarHeight / 2 + kBarDiff,
        center_x_ + kBarWidth / 2 - kBarDiff,
        center_y_ + kBarHeight / 2 - kBarDiff,
        GameConst::kWhiteColor,
        TRUE);

    // 文字を描画
    const std::string bgm_str = std::format("BGM:{}", dxlib_resource_loader_ptr_->getSEVolumePercent());
    const int bgm_str_width =
        GetDrawStringWidthToHandle(bgm_str.c_str(), static_cast<int>(bgm_str.size()), font32_handle_);
    const int str_height = GetFontSizeToHandle(font32_handle_);

    DrawFormatStringToHandle(center_x_ - bgm_str_width / 2, center_y_ - kBarHeight / 2 + str_height / 2,
        GameConst::kBlackColor, font32_handle_, bgm_str.c_str());

    const std::string se_str = std::format("SE:{}", dxlib_resource_loader_ptr_->getSEVolumePercent());
    const int se_str_width =
        GetDrawStringWidthToHandle(se_str.c_str(), static_cast<int>(se_str.size()), font32_handle_);

    DrawFormatStringToHandle(center_x_ - se_str_width / 2, center_y_ + kBarHeight / 2 - str_height * 3 / 2,
        GameConst::kBlackColor, font32_handle_, se_str.c_str());

    // +5, +1, +5, +1 の文字を描画
    const int plus_width = GetDrawStringWidthToHandle("+1", 3, font32_handle_);

    DrawFormatStringToHandle(center_x_ - kBarWidth / 2 + plus_width * 1 / 2, center_y_ - kBarHeight / 2 + str_height,
        GameConst::kBlackColor, font32_handle_, "+5", dxlib_resource_loader_ptr_->getSEVolumePercent());

    DrawFormatStringToHandle(center_x_ - kBarWidth / 2 + plus_width * 4 / 2, center_y_ - kBarHeight / 2 + str_height,
        GameConst::kBlackColor, font32_handle_, "+1", dxlib_resource_loader_ptr_->getSEVolumePercent());

    DrawFormatStringToHandle(center_x_ + kBarWidth / 2 - plus_width * 3 / 2, center_y_ - kBarHeight / 2 + str_height,
        GameConst::kBlackColor, font32_handle_, "+5", dxlib_resource_loader_ptr_->getSEVolumePercent());

    DrawFormatStringToHandle(center_x_ + kBarWidth / 2 - plus_width * 6 / 2, center_y_ - kBarHeight / 2 + str_height,
        GameConst::kBlackColor, font32_handle_, "+1", dxlib_resource_loader_ptr_->getSEVolumePercent());
}

bool SoundChangeBar::isHovered(int mouse_x, int mouse_y) const {
    return false;
}

void SoundChangeBar::initHoverState(bool is_hovered) {}

void SoundChangeBar::callbackWhenClicked() {}

void SoundChangeBar::callbackWhenHoverStarted() {}

void SoundChangeBar::callbackWhenHoverEnded() {}

}  // namespace match_stick
