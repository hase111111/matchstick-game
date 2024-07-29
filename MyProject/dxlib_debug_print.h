
#pragma once

#include <string>

namespace match_stick {

namespace debug_print_internal {

void debug_print(const std::string& str);

}  // namespace debug_print_internal

}  // namespace match_stick

#ifdef _DEBUG

#define DEBUG_PRINT(str) ::match_stick::debug_print_internal::debug_print(str)

#else

#define DEBUG_PRINT(str) ((void)0)

#endif  // _DEBUG
