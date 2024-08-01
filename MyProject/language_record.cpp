
#include "dxlib_assert.h"
#include "language_record.h"

namespace match_stick {

std::string LanguageRecord::get(const std::string& key) const {
    ASSERT(records_.find(key) != records_.end(), "LanguageRecord::Get: key not found: " + key);
    ASSERT(records_.at(key).find(current_country_) != records_.at(key).end(),
           "LanguageRecord::Get: country not found. key is " + key +
           "country code is " + std::to_string(static_cast<int>(current_country_)));

    return records_.at(key).at(current_country_);
}

void LanguageRecord::set(const std::string& key, Country country, const std::string& value) {
    records_[key][country] = value;
}

}  // namespace match_stick
