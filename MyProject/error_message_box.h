
//! @file error_message_box.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

#include <string>

#include <Dxlib.h>

namespace match_stick {

//! @class ErrorMessageBox
//! @brief エラーメッセージを表示するクラス．
//! 名前空間でもよかったか．
class ErrorMessageBox final {
public:
    //! @brief エラーメッセージを表示する．
    //! 静的メソッド．
    static void show(const std::string err_str) {
        MessageBox(NULL, TEXT(err_str.c_str()), TEXT("報告"), MB_ICONERROR);
    }
};

}  // namespace match_stick
