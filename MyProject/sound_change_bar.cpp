
#include "sound_change_bar.h"

#include <DxLib.h>

#include "dxlib_assert.h"

namespace match_stick {

SoundChangeBar::SoundChangeBar(
    const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr,
    int x, int y) :
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr),
    center_x_(x),
    center_y_(y) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
}


bool SoundChangeBar::update() {
    return true;
}

void SoundChangeBar::draw() const {
    DrawBox(center_x_ - 100, center_y_ - 10, center_x_ + 100, center_y_ + 10, GetColor(0, 255, 255), TRUE);
}

bool SoundChangeBar::isHovered(int mouse_x, int mouse_y) const {
    return false;
}

void SoundChangeBar::initHoverState(bool is_hovered) {}

void SoundChangeBar::callbackWhenClicked() {}

void SoundChangeBar::callbackWhenHoverStarted() {}

void SoundChangeBar::callbackWhenHoverEnded() {}

}  // match_stick
