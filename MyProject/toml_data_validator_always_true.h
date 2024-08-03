
#pragma once

#include <string>
#include <tuple>

#include "dxlib_debug_print.h"
#include "interface_toml_data_validator.h"


namespace match_stick {

//! @class TomlDataValidatorAlwaysTrue
//! @brief 常に trueを返す ITomlDataValidator の実装クラス．
//! @tparam T 検証対象の型．
template <typename T>
class TomlDataValidatorAlwaysTrue final : public ITomlDataValidator<T> {
public:
    std::tuple<bool, std::string> Validate([[maybe_unused]] const T& toml_data) const override {
        DEBUG_PRINT("(No validation is performed in the current configuration.)");
        return { true, "" };
    }
};

}  // namespace match_stick
