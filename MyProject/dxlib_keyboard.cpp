﻿
#include "dxlib_keyboard.h"

#include <DxLib.h>


namespace match_stick {

DxLibKeyboard::DxLibKeyboard() {

    for (int i = 0; i < kKeyNum; i++) {
        key_releasing_counter_[i] = 0;
        key_pressing_counter_[i] = 0;
    }
}

void DxLibKeyboard::update() {

    char now_key_status[kKeyNum];
    GetHitKeyStateAll(now_key_status);  // 今のキーの入力状態を取得．

    for (int i = 0; i < kKeyNum; ++i) {
        if (now_key_status[i] != 0) {
            // i番のキーが押されていたら．

            if (key_releasing_counter_[i] > 0) {

                // 離されカウンタが0より大きければ．
                key_releasing_counter_[i] = 0;  // 0に戻す．
            }

            key_pressing_counter_[i]++;  // 押されカウンタを増やす．
        }
        else {
            // i番のキーが離されていたら．
            if (key_pressing_counter_[i] > 0) {
                // 押されカウンタが0より大きければ．
                key_pressing_counter_[i] = 0;  // 0に戻す．
            }

            key_releasing_counter_[i]++;  // 離されカウンタを増やす．
        }
    }
}

int DxLibKeyboard::getPressingCount(const int key_code) const {

    if (!isAvailableCode(key_code)) {
        return -1;
    }

    return key_pressing_counter_[key_code];
}

int DxLibKeyboard::getReleasingCount(const int key_code) const {

    if (!isAvailableCode(key_code)) {
        return -1;
    }

    return key_releasing_counter_[key_code];
}

bool DxLibKeyboard::isAvailableCode(const int key_code) const {

    if (!(0 <= key_code && key_code < kKeyNum)) {
        return false;
    }

    return true;
}

}  // namespace homrerun
