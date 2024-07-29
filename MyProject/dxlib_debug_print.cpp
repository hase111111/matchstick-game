
#include "dxlib_debug_print.h"

#include <DxLib.h>

void match_stick::debug_print_internal::debug_print(const std::string& str) {
    printfDx("%s\n", str.c_str());
}
