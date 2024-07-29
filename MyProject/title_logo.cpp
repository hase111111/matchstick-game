
#include "title_logo.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

TitleLogo::TitleLogo(const std::shared_ptr<const LanguageRecord>& language_record_ptr, const std::shared_ptr<FontLoader>& font_loader) :
    big_font_handle_(font_loader->LoadAndGetFontHandle("data/font/PixelMplus10_size64.dft")),
    middle_font_handle_(font_loader->LoadAndGetFontHandle("data/font/PixelMplus10_size32.dft")),
    small_font_handle_(font_loader->LoadAndGetFontHandle("data/font/PixelMplus10_size20.dft")),
    game_title_(language_record_ptr->get("game_title", LanguageRecord::Country::kJapan)),
    announce_(language_record_ptr->get("press_any_key_to_start", LanguageRecord::Country::kJapan)),
    copy_right_(language_record_ptr->get("copy_right", LanguageRecord::Country::kJapan)) {
}

void TitleLogo::update() {
    ++counter_;
}

void TitleLogo::draw() const {
    const unsigned int color = GetColor(0, 0, 0);

    //タイトル
    const int game_title_len = GetDrawStringWidthToHandle(game_title_.c_str(), (int)game_title_.size(), big_font_handle_);
    DrawFormatStringToHandle((Define::WIN_SIZEX - game_title_len) / 2, Define::WIN_SIZEY / 8, color, big_font_handle_, game_title_.c_str());

    //アナウンス
    const int announce_len = GetDrawStringWidthToHandle(announce_.c_str(), (int)announce_.size(), middle_font_handle_);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * abs(cos(counter_ / blink_period_))));
    DrawFormatStringToHandle((Define::WIN_SIZEX - announce_len) / 2, Define::WIN_SIZEY * 3 / 4, color, middle_font_handle_, announce_.c_str());
    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

    //コピーライト
    const int copy_right_len = GetDrawStringWidthToHandle(copy_right_.c_str(), (int)copy_right_.size(), small_font_handle_);
    DrawFormatStringToHandle(Define::WIN_SIZEX - copy_right_len - 10, Define::WIN_SIZEY - 30, color, small_font_handle_, copy_right_.c_str());
}

}  // namespace match_stick
