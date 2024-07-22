
#ifndef HOMERUN_LANGUAGE_RECORED_H_
#define HOMERUN_LANGUAGE_RECORED_H_

#include <map>
#include <string>

namespace homerun
{

class LanguageRecord final
{
public:
    enum class Country
    {
        kJapan,
        kEnglish,
    };

    std::string Get(const std::string& key, Country country) const;

    void Set(const std::string& key, Country country, const std::string& value);

private:
    std::map<std::string, std::map<Country, std::string>> records_;
};

}  // namespace homerun

#endif  // HOMERUN_LANGUAGE_RECORED_H_
