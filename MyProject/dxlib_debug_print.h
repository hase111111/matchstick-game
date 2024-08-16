
#pragma once

#include <string>

namespace match_stick {

namespace debug_print_internal {

enum class DebugPrintType {
    kWarning,       //!< 警告
    kError,         //!< エラー
    kInfo,          //!< 一般的な情報
    kImportant,     //!< 重要な情報
    kDebug,         //!< デバッグ情報
};

void createConsole();

void debugPrint(const std::string& str, DebugPrintType type);

constexpr bool color_can_change = false;

}  // namespace debug_print_internal

}  // namespace match_stick

#ifdef _DEBUG

#define PREPAER_DEBUG_PRINT() ::match_stick::debug_print_internal::createConsole()

#define DEBUG_PRINT(str) \
::match_stick::debug_print_internal::debugPrint(str, ::match_stick::debug_print_internal::DebugPrintType::kDebug) 

#define DEBUG_PRINT_WARNING(str) \
::match_stick::debug_print_internal::debugPrint(str, ::match_stick::debug_print_internal::DebugPrintType::kWarning)

#define DEBUG_PRINT_ERROR(str) \
::match_stick::debug_print_internal::debugPrint(str, ::match_stick::debug_print_internal::DebugPrintType::kError)

#define DEBUG_PRINT_IMPORTANT(str) \
::match_stick::debug_print_internal::debugPrint(str, ::match_stick::debug_print_internal::DebugPrintType::kImportant)

#define DEBUG_PRINT_INFO(str) \
::match_stick::debug_print_internal::debugPrint(str, ::match_stick::debug_print_internal::DebugPrintType::kInfo)


#else

#define PREPAER_DEBUG_PRINT() ((void)0)

#define DEBUG_PRINT(str) ((void)0)

#define DEBUG_PRINT_WARNING(str) ((void)0)

#define DEBUG_PRINT_ERROR(str) ((void)0)

#define DEBUG_PRINT_IMPORTANT(str) ((void)0)

#define DEBUG_PRINT_INFO(str) ((void)0)

#endif  // _DEBUG
