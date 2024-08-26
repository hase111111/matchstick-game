
#include "dxlib_debug_print.h"

#include <iostream>
#include <iomanip>

#include <DxLib.h>

#include "error_message_box.h"
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

    if (AllocConsole() == FALSE) {
        ErrorMessageBox::show("createConsole コンソールの作成に失敗しました。");
        is_console_created = false;
        return;
    }

    freopen_s(&fp, "CONOUT$", "w", stdout);  // 標準出力(stdout)を新しいコンソールに向ける
    freopen_s(&fp, "CONOUT$", "w", stderr);  // 標準エラー出力(stderr)を新しいコンソールに向ける

    std::cout << std::endl;  // 見やすさのための改行

    is_console_created = true;
}

void runTest() {
    // コンソールが作成されていない場合は，テストを実行しない
    if (!is_console_created) {
        ErrorMessageBox::show("runTest コンソールが作成されていません。");
        return;
    }

    // デバッグプリントを無効にする
    debug_print_off = true;

    TestRunner test_runner;
    const bool res = test_runner.run();

    // テスト結果を表示

    std::cout << std::endl;  // 見やすさのための改行

    if (res) {
        DEBUG_PRINT_INFO("Test Success.");
    } else {
        DEBUG_PRINT_ERROR("Test Failed.");
    }

    // デバッグプリントを有効にする
    debug_print_off = false;
}

void debugPrint(const std::string& func_name, const std::string& str, const DebugPrintType type) {
    // デバッグプリントが無効の場合は，何もしない
    if (debug_print_off) {
        return;
    }

    const std::string text = changeFunctionMacroToString(func_name) + "\n\t";

    // 番号を表示，3桁右詰め
    std::cout << std::right << std::setw(3) << std::setfill('0') << print_count++ << " : ";

    // デバッグ情報の種類を表示
    std::cout << "Type [" << string_util::EnumToStringRemoveTopK(type) << "] ";

    if (type == DebugPrintType::kImportant) {
        std::cout << std::endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(type));
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << text << str << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        // 色をリセット
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        std::cout << text;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(type));
        std::cout << str << std::endl;
        // 色をリセット
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    std::cout << std::endl;
}

}  // namespace match_stick::debug_print_internal
