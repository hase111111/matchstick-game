
#pragma once

#include <string>

#include <Dxlib.h>

class ErrorMessage final {
public:
    static void show(const std::string err_str) {
        MessageBox(NULL, TEXT(err_str.c_str()), TEXT("報告"), MB_ICONERROR);
    }
};
