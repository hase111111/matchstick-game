
#include "language_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

LanguageBackGroundBase::LanguageBackGroundBase(const std::shared_ptr<LanguageRecord>& language_record_ptr,
                                               const std::shared_ptr<FontLoader>& font_loader_ptr,
                                               const std::shared_ptr<ImageLoader>& img_loader_ptr) :
    title_text_(language_record_ptr->get("language_title")),
    font_handle_(font_loader_ptr->loadAndGetFontHandle("data/font/azuki_font48.dft")),
    icon_handle_(img_loader_ptr->loadAndGetImageHandle("data/img/icon_language.png")) {}

void LanguageBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, color_white, TRUE);

    // アイコン 
    const int icon_pos_x = 70;
    const int icon_pos_y = 60;
    DrawRotaGraph(icon_pos_x, icon_pos_y, 0.6, 0.0, icon_handle_, TRUE);

    // タイトル
    DrawStringToHandle(icon_pos_x + 50, icon_pos_y - 25, title_text_.c_str(), color_back, font_handle_, color_white);
}

}  // namespace match_stick
