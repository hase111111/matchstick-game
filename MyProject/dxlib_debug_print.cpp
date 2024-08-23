
#include "dxlib_debug_print.h"

#include <iostream>
#include <iomanip>

#include <DxLib.h>

#include "string_util.h"
#include "test_runner.h"

namespace {

std::string changeFunctionMacroToString(const std::string& func_name) {
    // match_stick::をすべて削除
    std::string str = "Class Name [" + func_name;
    const std::string match_stick = "match_stick::";

    while (true) {
        const size_t pos = str.find(match_stick);
        if (pos == std::string::npos) {
            break;
        }
        str.erase(pos, match_stick.size());
    }

    // struct ，class を削除
    const std::string struct_str = "struct ";
    const std::string class_str = "class ";
    while (true) {
        const size_t pos = str.find(struct_str);
        if (pos == std::string::npos) {
            break;
        }
        str.erase(pos, struct_str.size());
    }

    // :: を削除し，カンマで置き換える．
    const std::string replace_str = "], Func Name [";
    while (true) {
        const size_t pos = str.find("::");
        if (pos == std::string::npos) {
            break;
        }
        str.replace(pos, 2, replace_str);
    }

    str += "]";

    return str;
}

}  // namespace

namespace match_stick::debug_print_internal {

void createConsole() {
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);  // 標準出力(stdout)を新しいコンソールに向ける
    freopen_s(&fp, "CONOUT$", "w", stderr);  // 標準エラー出力(stderr)を新しいコンソールに向ける

    std::cout << std::endl;  // 見やすさのための改行
}

void runTest() {
    TestRunner test_runner;
    const bool res = test_runner.run();

    // テスト結果を表示

    std::cout << std::endl;  // 見やすさのための改行

    if (res) {
        DEBUG_PRINT_INFO("Test Success.");
    } else {
        DEBUG_PRINT_ERROR("Test Failed.");
    }
}

void debugPrint(const std::string& func_name, const std::string& str, const DebugPrintType type) {
    const std::string text = changeFunctionMacroToString(func_name) + "\n\t" + str;

    // 番号を表示，3桁右詰め
    std::cout << std::right << std::setw(3) << std::setfill('0') << print_count++ << " : ";

    // デバッグ情報の種類を表示
    std::cout << "Type [" << string_util::EnumToStringRemoveTopK(type) << "] ";

    if (type == DebugPrintType::kImportant) {
        std::cout << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << text << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
    } else {
        std::cout << text << std::endl;
    }

    std::cout << std::endl;
}

}  // namespace match_stick::debug_print_internal
