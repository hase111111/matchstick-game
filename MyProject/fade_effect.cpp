
#include "fade_effect.h"

#include <DxLib.h>

#include "game_const.h"
#include "dxlib_debug_print.h"

namespace match_stick {

FadeEffect::FadeEffect(
    int fade_time, FadeType fade_type, std::function<void()> callback) :
    fade_time_(fade_time),
    fade_type_(fade_type),
    callback_(callback) {}

bool FadeEffect::update() {
    if (counter_ == fade_time_) {
        return false;
    }

    counter_++;

    if (counter_ == fade_time_) {
        DEBUG_PRINT_INFO("CallBack function called");
        callback_();
    }

    return true;
}

void FadeEffect::draw() const {
    if (fade_type_ == FadeType::kFadeOut) {
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, counter_ * 255 / fade_time_);
    } else {
        const int blend = 255 * (fade_time_ - counter_) / fade_time_;
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
    }

    DxLib::DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, DxLib::GetColor(0, 0, 0), TRUE);

    DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

}  // namespace match_stick
