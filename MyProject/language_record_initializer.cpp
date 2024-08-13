
#include "language_record_initializer.h"

#include <fstream>

#include <magic_enum.hpp>

#include "dxlib_assert.h"

namespace match_stick {

LanguageRecord LanguageRecordInitializer::initialize(const LanguageRecord::Country country) {
    LanguageRecord record;

    for (const auto& country_enum : magic_enum::enum_values<LanguageRecord::Country>()) {
        const std::string file_path = getLanguageFilePath(country_enum);

        std::ifstream ifs(file_path);
        ASSERT(ifs.is_open(), "Failed to open file: " + file_path);

        std::string line;

        while (std::getline(ifs, line)) {
            // 空白行，#で始まるコメント行は無視
            if (line.empty() || line[0] == '#') {
                continue;
            }

            const size_t comma_pos = line.find(",");
            ASSERT(comma_pos != std::string::npos, "Invalid format: " + line);

            const std::string key = line.substr(0, comma_pos);
            const std::string value = line.substr(comma_pos + 1);

            record.set(key, country_enum, value);
        }
    }

    record.setCurrentCountry(country);

    return record;
}

std::string LanguageRecordInitializer::getLanguageFilePath(LanguageRecord::Country country) const {
    switch (country) {
    case LanguageRecord::Country::kJapanese: {
        return "data/language/jpn.csv";
    }
    case LanguageRecord::Country::kEnglish: {
        return "data/language/eng.csv";
    }
    case LanguageRecord::Country::kChinese: {
        return "data/language/chn.csv";
    }
    case LanguageRecord::Country::kKorean: {
        return "data/language/kor.csv";
    }
    default: {
        ASSERT_MUST_NOT_REACH_HERE();
        return "";
    }
    }
}

}  // namespace match_stick
