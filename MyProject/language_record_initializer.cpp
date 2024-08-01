
#include "language_record_initializer.h"

namespace match_stick {

LanguageRecord LanguageRecordInitializer::initialize() {
    LanguageRecord record;

    using enum LanguageRecord::Country;

    //! @todo テキストの初期化をファイルから行うようにする．

    record.set("game_title", kJapan, "マッチ棒ゲーム");
    record.set("game_title", kEnglish, "Match Stick Game");

    record.set("press_z_key_to_start", kJapan, "Zキーを押してスタート");
    record.set("press_z_key_to_start", kEnglish, "Press z key to start");

    record.set("click_left_to_start", kJapan, "左クリックでスタート");
    record.set("click_left_to_start", kEnglish, "Click left to start");

    record.set("copy_right", kJapan, "Copy right 2021 Saidai Game Production");
    record.set("copy_right", kEnglish, "Copy right 2021 Saidai Game Production");

    return record;
}

}  // namespace match_stick
