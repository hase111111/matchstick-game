
#include "language_record_initializer.h"

namespace match_stick {

LanguageRecord LanguageRecordInitializer::initialize() {
    LanguageRecord record;

    using enum LanguageRecord::Country;

    //! @todo テキストの初期化をファイルから行うようにする．

    record.set("game_title", kJapan, "マッチ棒ゲーム");
    record.set("game_title", kEnglish, "Match Stick Game");

    record.set("press_any_key_to_start", kJapan, "何かキーを押してスタート");
    record.set("press_any_key_to_start", kEnglish, "Press any key to start");

    record.set("copy_right", kJapan, "Copy right 2021 Saidai Game Production");
    record.set("copy_right", kEnglish, "Copy right 2021 Saidai Game Production");

    return record;
}

}  // namespace match_stick
