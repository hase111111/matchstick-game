
#pragma once

#include <string>

#include "language_record.h"

namespace match_stick {

class LanguageRecordInitializer final {
public:
    LanguageRecord initialize(LanguageRecord::Country country);

private:
    std::string getLanguageFilePath(LanguageRecord::Country country) const;
};

}  // namespace match_stick
