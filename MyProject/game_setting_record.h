
#pragma once

#include "language_record.h"
#include "string_util.h"
#include "toml_serialize_macro.h"

namespace match_stick {

struct GameSettingRecord final {
    LanguageRecord::Country language_country{ LanguageRecord::Country::kEnglish };
};

MATCH_STICK_TOML11_DESCRIPTION_CLASS(GameSettingRecord) {
    MATCH_STICK_TOML11_FILE_NO_DESCRIPTION();

    MATCH_STICK_TOML11_TABLE_ADD_DESCRIPTION("language", "");

    MATCH_STICK_TOML11_VARIABLE_ADD_DESCRIPTION(language_country, "language",
        string_util::EnumValuesToString<LanguageRecord::Country>(","));
};

}  // namespace match_stick

MATCH_STICK_TOML11_SERIALIZE(match_stick::GameSettingRecord, language_country);
