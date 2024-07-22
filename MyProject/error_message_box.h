
#pragma once

#include <string>

#include <Dxlib.h>

namespace match_stick {

class ErrorMessageBox final {
public:
    static void show(const std::string err_str) {
        MessageBox(NULL, TEXT(err_str.c_str()), TEXT("報告"), MB_ICONERROR);
    }
};

}  // namespace match_stick
