
#include "setting_back_ground_base.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"
#include "math_const.h"

namespace match_stick {

SettingBackGroundBase::SettingBackGroundBase(
    const std::shared_ptr<const LanguageRecord>& language_record_ptr,
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    title_text_(language_record_ptr->getValue("setting_title")),
    font48_handle_(dxlib_resource_loader_ptr->getFontHandle(
        language_record_ptr->getCurrentCountry(), "data/font/azuki_font48.dft")),
    icon_handle_(dxlib_resource_loader_ptr->getImageHandle("data/img/icon_setting.png")) {
    // nullptr check
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);
}

bool SettingBackGroundBase::update() {
    ++counter_;

    return true;
}

void SettingBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, color_white, TRUE);

    // アイコン
    const int icon_pos_x = 120;
    const int icon_pos_y = 60;
    const double angle = counter_ * MathConst<double>::kPi / 360;

    DrawRotaGraph(icon_pos_x, icon_pos_y, 0.6, angle, icon_handle_, TRUE);

    // タイトル
    DrawStringToHandle(icon_pos_x + 50, icon_pos_y - 25, title_text_.c_str(), color_back, font48_handle_, color_white);
}

}  // namespace match_stick
