
#pragma once

#include <map>
#include <string>

namespace match_stick {

class LanguageRecord final {
public:
    enum class Country {
        kJapan,
        kEnglish,
        kChina,
        kKorea,
    };

    std::string get(const std::string& key) const;

    void set(const std::string& key, Country country, const std::string& value);

    bool has(const std::string& key) const;

    inline Country getCurrentCountry() const {
        return current_country_;
    }

    void setCurrentCountry(Country country) {
        current_country_ = country;
    }

    static bool isEnglish(Country country);

private:
    std::map<std::string, std::map<Country, std::string>> records_;

    Country current_country_{ Country::kJapan };
};

}  // namespace match_stick
