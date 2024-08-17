
#include "language_back_ground_base.h"

#include <DxLib.h>

#include "define.h"
#include "dxlib_assert.h"

namespace match_stick {

LanguageBackGroundBase::LanguageBackGroundBase(const std::shared_ptr<const LanguageRecord>& lang,
                                               const std::shared_ptr<const FontLoader>& font_loader_ptr,
                                               const std::shared_ptr<const ImageLoader>& img_loader_ptr) :
    title_text_(lang->get("language_title")),
    font_handle_(font_loader_ptr->getFontHandle(lang->getCurrentCountry(), "data/font/azuki_font48.dft")),
    icon_handle_(img_loader_ptr->getImageHandle("data/img/icon_language.png")) {
    // ポインタのチェック
    ASSERT_NOT_NULL_PTR(lang);
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(img_loader_ptr);
}

void LanguageBackGroundBase::draw() const {
    const unsigned int color_back = GetColor(0x21, 0x21, 0x21);
    const unsigned int color_white = GetColor(0xda, 0xda, 0xda);

    // 下地
    DrawBox(0, 0, Define::kWindowSizeX, Define::kWindowSizeY, color_white, TRUE);

    // アイコン
    const int icon_pos_x = 120;
    const int icon_pos_y = 60;
    DrawRotaGraph(icon_pos_x, icon_pos_y, 0.6, 0.0, icon_handle_, TRUE);

    // タイトル
    DrawStringToHandle(icon_pos_x + 50, icon_pos_y - 25, title_text_.c_str(), color_back, font_handle_, color_white);
}

}  // namespace match_stick
