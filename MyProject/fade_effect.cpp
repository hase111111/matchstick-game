﻿
#include "fade_effect.h"

#include <DxLib.h>

#include "define.h"
#include "dxlib_debug_print.h"

namespace match_stick {

FadeEffect::FadeEffect(
    int fade_time, FadeType fade_type, std::function<void()> callback) :
    fade_time_(fade_time),
    fade_type_(fade_type),
    callback_(callback) {
    DEBUG_PRINT("FadeEffect::FadeEffect() called");
}

FadeEffect::~FadeEffect() {
    DEBUG_PRINT("FadeEffect::~FadeEffect() called");
}

bool FadeEffect::update() {
    if (counter_ == fade_time_) {
        return false;
    }

    counter_++;

    if (counter_ == fade_time_) {
        callback_();
    }

    return true;
}

void FadeEffect::draw() const {
    if (fade_type_ == FadeType::kFadeOut) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, counter_ * 255 / fade_time_);
    } else {
        const int blend = 255 * (fade_time_ - counter_) / fade_time_;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);
    }

    DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0, 0, 0), TRUE);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

}  // namespace match_stick
