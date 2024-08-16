
#include "dxlib_debug_print.h"

#include <iostream>

#include <DxLib.h>


namespace match_stick::debug_print_internal {

void createConsole() {
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);  // 標準出力(stdout)を新しいコンソールに向ける
    freopen_s(&fp, "CONOUT$", "w", stderr);  // 標準エラー出力(stderr)を新しいコンソールに向ける
}

void debugPrint(const std::string& str, const DebugPrintType type) {
    // type に応じて色を変える

    switch (type) {
    case DebugPrintType::kWarning: {
        // 黄色
        std::cout << "\x1b[33m";
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kError: {
        // 赤色
        std::cout << "\x1b[31m";
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kInfo: {
        // 通常
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kImportant: {
        // 横線を引く
        std::cout << "----------------------------------------" << std::endl;
        std::cout << str << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        return;
    }
    case DebugPrintType::kDebug: {
        // 灰色
        std::cout << "\x1b[31m";
        std::cout << str << std::endl;
        return;
    }
    }
}

}  // namespace match_stick::debug_print_internal
