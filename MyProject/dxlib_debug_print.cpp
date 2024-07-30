
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

void debugPrint(const std::string& str) {
    std::cout << str << std::endl;
}

}  // namespace match_stick::debug_print_internal
