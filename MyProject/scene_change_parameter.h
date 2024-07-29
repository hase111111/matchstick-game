
#pragma once

#include <map>
#include <string>
#include <variant>

#include "dxlib_assert.h"

namespace match_stick {

// パラメータとして利用できるか確認するコンセプト
template <typename T>
concept IsParameter = std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, std::string>;

class SceneChangeParameter final {
public:
    SceneChangeParameter() = default;
    ~SceneChangeParameter() = default;

    bool hasParameter(const std::string& key) const {
        return parameters_.find(key) != parameters_.end();
    }

    template <IsParameter T>
    void setParameter(const std::string& key, T value) {
        parameters_[key] = value;
    }

    template <IsParameter T>
    T getParameter(const std::string& key) const {
        auto it = parameters_.find(key);

        ASSERT(it != parameters_.end(), "Parameter not found. Key is " + key);

        return std::get<T>(it->second);
    }

    void reset();

private:
    std::map<std::string, std::variant<int, double, std::string>> parameters_;
};

}  // namespace match_stick
