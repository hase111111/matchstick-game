
#include "language_record_initializer.h"

#include <fstream>

#include "dxlib_assert.h"

namespace match_stick {

LanguageRecord LanguageRecordInitializer::initialize(const LanguageRecord::Country country) {
    LanguageRecord record;

    const std::string file_path = getLanguageFilePath(country);

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

        record.set(key, country, value);
    }

    return record;
}

std::string LanguageRecordInitializer::getLanguageFilePath(LanguageRecord::Country country) const {
    switch (country) {
    case LanguageRecord::Country::kJapan: {
        return "data/language/jp.csv";
    }
    case LanguageRecord::Country::kEnglish: {
        return "data/language/en.csv";
    }
    default: {
        ASSERT_MUST_NOT_REACH_HERE();
        return "";
    }
    }
}

}  // namespace match_stick
