
#pragma once

#include <string>

namespace match_stick {

namespace debug_print_internal {

void createConsole();

void debugPrint(const std::string& str);

}  // namespace debug_print_internal

}  // namespace match_stick

#ifdef _DEBUG

#define PREPAER_DEBUG_PRINT() ::match_stick::debug_print_internal::createConsole()

#define DEBUG_PRINT(str) ::match_stick::debug_print_internal::debugPrint(str)

#else

#define PREPAER_DEBUG_PRINT() ((void)0)

#define DEBUG_PRINT(str) ((void)0)

#endif  // _DEBUG
