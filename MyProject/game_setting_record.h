
#pragma once

#include "language_record.h"
#include "string_util.h"
#include "toml_serialize_macro.h"

namespace match_stick {

struct GameSettingRecord final {
    LanguageRecord::Country language_country{ LanguageRecord::Country::kEnglish };

    int window_width{ 1280 };
    int window_height{ 720 };

    bool is_full_screen{ false };

    int sound_volume{ 100 };
    int bgm_volume{ 100 };
};

MATCH_STICK_TOML11_DESCRIPTION_CLASS(GameSettingRecord) {
    MATCH_STICK_TOML11_FILE_NO_DESCRIPTION();

    MATCH_STICK_TOML11_TABLE_ADD_DESCRIPTION(
        "language", "This is a setting for language.",
        "window", "This is a setting for window size and full screen.",
        "sound", "This is a setting for sound and volume.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(language_country, "language",
        "param list : [ " + string_util::EnumValuesToString<LanguageRecord::Country>(" , ") + " ]");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(window_width, "window", "The value range is from 540 to 1080.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(window_height, "window", "The value range is from 960 to 1920.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(is_full_screen, "window", "The value is true or false.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(sound_volume, "sound", "The value range is from 0 to 100.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(bgm_volume, "sound", "The value range is from 0 to 100.");
};

}  // namespace match_stick

MATCH_STICK_TOML11_SERIALIZE(
    match_stick::GameSettingRecord,
    window_width, window_height, is_full_screen,
    language_country, sound_volume, bgm_volume);
