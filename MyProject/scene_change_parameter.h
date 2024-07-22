
#pragma once

#include <map>
#include <string>
#include <variant>

#include "dxlib_assert.h"

namespace match_stick
{

class SceneChangeParameter final
{
public:
    SceneChangeParameter() = default;
    ~SceneChangeParameter() = default;

    bool HasParameter(const std::string& key) const
    {
        return parameters_.find(key) != parameters_.end();
    }

    template <typename T,
        typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, std::string>>>
    void SetParameter(const std::string& key, T value)
    {
        parameters_[key] = value;
    }

    template <typename T,
        typename = std::enable_if_t<std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, std::string>>>
    T GetParameter(const std::string& key) const
    {
        auto it = parameters_.find(key);

        ASSERT(it != parameters_.end(), "Parameter not found. Key is " + key);

        return std::get<T>(it->second);
    }

    void Reset();

private:
    std::map<std::string, std::variant<int, double, std::string>> parameters_;
};

}  // namespace match_stick
