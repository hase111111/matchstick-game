
#include "fps_displayer.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

FpsDisplayer::FpsDisplayer(const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<const LanguageRecord>& lang,
                           const std::shared_ptr<const FontLoader>& font_loader_ptr) :
    fps_controller_ptr_(fps_controller_ptr),
    font_handle_(font_loader_ptr->getFontHandle(lang->getCurrentCountry(), "data/font/azuki_font20.dft")) {}

void FpsDisplayer::draw() const {
    const double fps = fps_controller_ptr_->getCurrentFps();

    const int x_pos = 10;
    const int y_pos = Define::kWindowSizeY - 20;

    if (fps < 0) {
        // 0以下を返す時，未だFPSが計測されていないことを意味する
        DrawFormatStringToHandle(x_pos, y_pos, GetColor(0, 0, 0), font_handle_, "FPS: --");
    } else {
        int fps_int = static_cast<int>(fps);
        int fps_decimal = static_cast<int>((fps - fps_int) * 10);
        DrawFormatStringToHandle(x_pos, y_pos, GetColor(0, 0, 0), font_handle_, "FPS: %d.%d", fps_int, fps_decimal);
    }
}

}  // namespace match_stick

