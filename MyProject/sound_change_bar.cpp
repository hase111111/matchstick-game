
#include "sound_change_bar.h"

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

    // バーの上に文字を描画
    DrawFormatStringToHandle(center_x_ - kBarWidth / 2 + 10, center_y_ - kBarHeight / 2 + 10,
        GameConst::kBlackColor, font32_handle_, "BGM:%d", dxlib_resource_loader_ptr_->getVolumePercent());
}

bool SoundChangeBar::isHovered(int mouse_x, int mouse_y) const {
    return false;
}

void SoundChangeBar::initHoverState(bool is_hovered) {}

void SoundChangeBar::callbackWhenClicked() {}

void SoundChangeBar::callbackWhenHoverStarted() {}

void SoundChangeBar::callbackWhenHoverEnded() {}

}  // namespace match_stick
