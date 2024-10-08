﻿
#include "language_record.h"

#include <magic_enum.hpp>

#include "dxlib_assert.h"

namespace match_stick {

std::string LanguageRecord::getValue(const std::string& key) const {
    ASSERT(records_.find(key) != records_.end(), "LanguageRecord::Get: key not found: " + key);
    ASSERT(records_.at(key).find(current_country_) != records_.at(key).end(),
        "LanguageRecord::Get: country not found. key is " + key +
        ", country code is " + magic_enum::enum_name(current_country_).data());

    return records_.at(key).at(current_country_);
}

void LanguageRecord::setValue(const std::string& key, Country country, const std::string& value) {
    records_[key][country] = value;
}

bool LanguageRecord::hasKey(const std::string& key) const {
    if (records_.find(key) == records_.end()) {
        return false;
    }

    if (records_.at(key).find(current_country_) == records_.at(key).end()) {
        return false;
    }

    return true;
}

bool LanguageRecord::isEnglish(const Country country) {
    return country == Country::kEnglish;
}

}  // namespace match_stick
