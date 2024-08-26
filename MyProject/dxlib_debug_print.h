
#pragma once

#include <string>

namespace match_stick {

//! @namespace match_stick::debug_print_internal
//! @brief デバッグ用のプリント関数を提供する名前空間
//! インターナルな関数にするため，深い階層にしている
namespace debug_print_internal {

//! @brief デバッグ用プリントが実行された回数
static int print_count = 0;

//! @brief デバッグ用のコンソールが作成されたかどうか
//! true: 作成された，false: 作成されていない
static bool is_console_created = false;

//! @brief デバッグ用のプリントを無効にするかどうか
//! true: 無効，false: 有効
static bool debug_print_off = false;

enum class DebugPrintType {
    kWarning,       //!< 警告
    kError,         //!< エラー
    kInfo,          //!< 一般的な情報
    kImportant,     //!< 重要な情報
    kDebug,         //!< デバッグ情報
};

//! @brief デバッグ用のコンソールを作成する
//! 作成に失敗した場合は，メッセージボックスを表示する
//! @details
//! DxLib はデバッグ用のコンソールを提供していないため，
//! Win32API の AllocConsole() を使用してコンソールを作成する．
//! また，標準出力を新しいコンソールに向けるために freopen_s() を使用する．
void createConsole();

//! @brief テストを実行する
//! 実行に失敗した場合は，メッセージボックスを表示する
//! @details
//! doctest で作成されたテストを実行する．
//! createConsole を実行していないと，テスト結果がコンソールに表示されない．
//! また，DxLib_Init が実行されるまえに実行する必要がある．
void runTest();

void debugPrint(const std::string& func_name, const std::string& str, DebugPrintType type);

}  // namespace debug_print_internal

}  // namespace match_stick

#ifdef _DEBUG

#define PREPAER_DEBUG_PRINT_AND_ACTIVATE_TEST() \
::match_stick::debug_print_internal::createConsole(); \
::match_stick::debug_print_internal::runTest();

#define DEBUG_PRINT(str) \
::match_stick::debug_print_internal::debugPrint( \
    __FUNCTION__, str, ::match_stick::debug_print_internal::DebugPrintType::kDebug)

#define DEBUG_PRINT_WARNING(str) \
::match_stick::debug_print_internal::debugPrint( \
    __FUNCTION__, str, ::match_stick::debug_print_internal::DebugPrintType::kWarning)

#define DEBUG_PRINT_ERROR(str) \
::match_stick::debug_print_internal::debugPrint( \
    __FUNCTION__, str, ::match_stick::debug_print_internal::DebugPrintType::kError)

#define DEBUG_PRINT_IMPORTANT(str) \
::match_stick::debug_print_internal::debugPrint( \
    __FUNCTION__, str, ::match_stick::debug_print_internal::DebugPrintType::kImportant)

#define DEBUG_PRINT_INFO(str) \
::match_stick::debug_print_internal::debugPrint( \
    __FUNCTION__, str, ::match_stick::debug_print_internal::DebugPrintType::kInfo)

#else

#define PREPAER_DEBUG_PRINT() ((void)0)

#define DEBUG_PRINT(str) ((void)0)

#define DEBUG_PRINT_WARNING(str) ((void)0)

#define DEBUG_PRINT_ERROR(str) ((void)0)

#define DEBUG_PRINT_IMPORTANT(str) ((void)0)

#define DEBUG_PRINT_INFO(str) ((void)0)

#endif  // _DEBUG
