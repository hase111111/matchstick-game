
#include "title_logo.h"

#include <DxLib.h>

#include "dxlib_assert.h"
#include "game_const.h"
#include "dxlib_debug_print.h"

namespace match_stick {

TitleLogo::TitleLogo(const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    dxlib_input_ptr_(dxlib_input_ptr),
    font64_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font64.dft")),
    font32_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font32.dft")),
    font20_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font20.dft")),
    game_title_(language_record_ptr->getValue("game_title")),
    announce_keyboard_text_(language_record_ptr->getValue("press_z_key_to_start")),
    announce_mouse_text_(language_record_ptr->getValue("click_left_to_start")),
    copy_right_text_(language_record_ptr->getValue("copy_right")) {
    // NULL チェック
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
}

bool TitleLogo::update() {
    ++counter_;

    return true;
}

void TitleLogo::draw() const {
    const unsigned int color = GetColor(0, 0, 0);

    // タイトル
    const int game_title_size = static_cast<int>(game_title_.size());
    const int game_title_len = GetDrawStringWidthToHandle(game_title_.c_str(), game_title_size, font64_handle_);
    const int title_x = (GameConst::kResolutionX - game_title_len) / 2;
    const int title_y = GameConst::kResolutionY / 8;
    DrawFormatStringToHandle(title_x, title_y, color, font64_handle_, game_title_.c_str());

    // キー入力を促すメッセージ
    std::string announce = (dxlib_input_ptr_->getInputType() == DxLibInput::InputType::kMouse) ?
        announce_mouse_text_ : announce_keyboard_text_;

    const int announce_size = static_cast<int>(announce.size());
    const int announce_len = GetDrawStringWidthToHandle(announce.c_str(), announce_size, font32_handle_);
    const int announce_x = (GameConst::kResolutionX - announce_len) / 2;
    const int announce_y = GameConst::kResolutionY * 3 / 4;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * abs(cos(counter_ / blink_period_))));
    DrawFormatStringToHandle(announce_x, announce_y, color, font32_handle_, announce.c_str());
    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

    // コピーライト
    const int copy_right_size = static_cast<int>(copy_right_text_.size());
    const int copy_right_len = GetDrawStringWidthToHandle(copy_right_text_.c_str(), copy_right_size, font20_handle_);
    const int copy_right_x = GameConst::kResolutionX - copy_right_len - 10;
    const int copy_right_y = GameConst::kResolutionY - 30;

    DrawFormatStringToHandle(copy_right_x, copy_right_y, color, font20_handle_, copy_right_text_.c_str());
}

}  // namespace match_stick
