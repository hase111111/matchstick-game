﻿
#include "dxlib_debug_print.h"

#include <iostream>
#include <iomanip>

#include <DxLib.h>


namespace match_stick::debug_print_internal {

void createConsole() {
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);  // 標準出力(stdout)を新しいコンソールに向ける
    freopen_s(&fp, "CONOUT$", "w", stderr);  // 標準エラー出力(stderr)を新しいコンソールに向ける
}

void debugPrint(const std::string& func_name, const std::string& str, const DebugPrintType type) {
    const std::string text = "[" + func_name + "] \n\t" + str;

    // 番号を表示，3桁右詰め
    std::cout << std::right << std::setw(3) << std::setfill('0') << print_count++ << " : ";

    switch (type) {
    case DebugPrintType::kWarning: {
        // 黄色
        if (color_can_change) {
            std::cout << "\x1b[33m";
        } else {
            std::cout << "Warning: ";
        }
        std::cout << text << std::endl;
        break;
    }
    case DebugPrintType::kError: {
        // 赤色
        if (color_can_change) {
            std::cout << "\x1b[31m";
        } else {
            std::cout << "Error: ";
        }
        std::cout << text << std::endl;
        break;
    }
    case DebugPrintType::kInfo: {
        // 通常
        if (color_can_change) {
            std::cout << "\x1b[39m";
        } else {
            std::cout << "Info: ";
        }
        std::cout << text << std::endl;
        break;
    }
    case DebugPrintType::kImportant: {
        // 横線を引く
        if (color_can_change) {
            std::cout << "\n";
            std::cout << "\x1b[39m";
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << text << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        } else {
            std::cout << "Important: \n";
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << text << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;
        }
        break;
    }
    case DebugPrintType::kDebug: {
        // 灰色
        if (color_can_change) {
            std::cout << "\x1b[31m";
        } else {
            std::cout << "Debug: ";
        }
        std::cout << text << std::endl;
        break;
    }
    }

    std::cout << std::endl;
}

}  // namespace match_stick::debug_print_internal
