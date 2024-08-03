
#pragma once

#include <string>
#include <tuple>


namespace match_stick {

//! @class ITomlDataValidator
//! @brief TOMLファイルのデータの検証を行う処理のインターフェース．
template <typename T>
class ITomlDataValidator {
public:
    virtual ~ITomlDataValidator() = default;

    //! @brief TOMLファイルのデータの検証を行う．
    //! @param[in] toml_data TOMLファイルのデータ．
    //! @return 検証結果．1つ目の要素は検証結果，2つ目の要素は検証失敗の理由．
    virtual std::tuple<bool, std::string> Validate(const T& toml_data) const = 0;
};

}  // namespace match_stick
