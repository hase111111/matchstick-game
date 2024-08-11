
#include "title_logo.h"

#include <DxLib.h>

#include "define.h"
#include "dxlib_debug_print.h"

namespace match_stick {

TitleLogo::TitleLogo(const std::shared_ptr<const DxLibInput>& input_ptr,
                     const std::shared_ptr<const LanguageRecord>& lang,
                     const std::shared_ptr<FontLoader>& font_loader) :
    input_ptr_(input_ptr),
    big_font_handle_(font_loader->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font64.dft")),
    middle_font_handle_(font_loader->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font32.dft")),
    small_font_handle_(font_loader->loadAndGetFontHandle(lang->getCurrentCountry(), "data/font/azuki_font20.dft")),
    game_title_(lang->get("game_title")),
    announce_keyboard_(lang->get("press_z_key_to_start")),
    announce_mouse_(lang->get("click_left_to_start")),
    copy_right_(lang->get("copy_right")) {
    DEBUG_PRINT("TitleLogo Constructor called");
}

TitleLogo::~TitleLogo() {
    DEBUG_PRINT("TitleLogo Destructor called");
}

bool TitleLogo::update() {
    ++counter_;

    return true;
}

void TitleLogo::draw() const {
    const unsigned int color = GetColor(0, 0, 0);

    // タイトル
    const int game_title_size = static_cast<int>(game_title_.size());
    const int game_title_len = GetDrawStringWidthToHandle(game_title_.c_str(), game_title_size, big_font_handle_);
    const int title_x = (Define::kWindowSizeX - game_title_len) / 2;
    const int title_y = Define::kWindowSizeY / 8;
    DrawFormatStringToHandle(title_x, title_y, color, big_font_handle_, game_title_.c_str());

    // キー入力を促すメッセージ
    std::string announce = (input_ptr_->getInputType() == DxLibInput::InputType::kMouse) ?
        announce_mouse_ : announce_keyboard_;

    const int announce_size = static_cast<int>(announce.size());
    const int announce_len = GetDrawStringWidthToHandle(announce.c_str(), announce_size, middle_font_handle_);
    const int announce_x = (Define::kWindowSizeX - announce_len) / 2;
    const int announce_y = Define::kWindowSizeY * 3 / 4;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * abs(cos(counter_ / blink_period_))));
    DrawFormatStringToHandle(announce_x, announce_y, color, middle_font_handle_, announce.c_str());
    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

    // コピーライト
    const int copy_right_size = static_cast<int>(copy_right_.size());
    const int copy_right_len = GetDrawStringWidthToHandle(copy_right_.c_str(), copy_right_size, small_font_handle_);
    const int copy_right_x = Define::kWindowSizeX - copy_right_len - 10;
    const int copy_right_y = Define::kWindowSizeY - 30;

    DrawFormatStringToHandle(copy_right_x, copy_right_y, color, small_font_handle_, copy_right_.c_str());
}

}  // namespace match_stick
