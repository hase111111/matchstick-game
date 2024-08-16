
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
        if (color_can_change) {
            std::cout << "\x1b[33m";
        } else {
            std::cout << "Warning: ";
        }
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kError: {
        // 赤色
        if (color_can_change) {
            std::cout << "\x1b[31m";
        } else {
            std::cout << "Error: ";
        }
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kInfo: {
        // 通常
        if (color_can_change) {
            std::cout << "\x1b[39m";
        } else {
            std::cout << "Info: ";
        }
        std::cout << str << std::endl;
        return;
    }
    case DebugPrintType::kImportant: {
        // 横線を引く
        if (color_can_change) {
            std::cout << "\x1b[39m";
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << str << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        } else {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Important: " << str << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }
        return;
    }
    case DebugPrintType::kDebug: {
        // 灰色
        if (color_can_change) {
            std::cout << "\x1b[31m";
        } else {
            std::cout << "Debug: ";
        }
        std::cout << str << std::endl;
        return;
    }
    }
}

}  // namespace match_stick::debug_print_internal
