
#pragma once

#include <map>
#include <string>

namespace match_stick {

class LanguageRecord final {
public:
    enum class Country {
        kJapan,
        kEnglish,
    };

    std::string get(const std::string& key, Country country) const;

    void set(const std::string& key, Country country, const std::string& value);

private:
    std::map<std::string, std::map<Country, std::string>> records_;
};

}  // namespace match_stick
