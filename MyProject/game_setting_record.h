
#pragma once

#include "language_record.h"
#include "string_util.h"
#include "toml_serialize_macro.h"

namespace match_stick {

struct GameSettingRecord final {
    LanguageRecord::Country language_country{ LanguageRecord::Country::kEnglish };

    int sound_volume{ 50 };
    int bgm_volume{ 50 };
};

MATCH_STICK_TOML11_DESCRIPTION_CLASS(GameSettingRecord) {
    MATCH_STICK_TOML11_FILE_NO_DESCRIPTION();

    MATCH_STICK_TOML11_TABLE_ADD_DESCRIPTION(
        "language", "This is a setting for language.",
        "sound", "This is a setting for sound and volume.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(language_country, "language",
        "param list : [ " + string_util::EnumValuesToString<LanguageRecord::Country>(" , ") + " ]");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(sound_volume, "sound", "The value range is from 0 to 100.");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(bgm_volume, "sound", "The value range is from 0 to 100.");
};

}  // namespace match_stick

MATCH_STICK_TOML11_SERIALIZE(match_stick::GameSettingRecord, language_country, sound_volume, bgm_volume);
