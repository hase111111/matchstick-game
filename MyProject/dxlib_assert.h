
#pragma once

#include <source_location>
#include <string>

#include <Windows.h>


namespace match_stick {

namespace assert_internal {

void ErrorAssert(const std::string& conditional_expression, const std::string& error_mes,
                 const std::string& file, const std::string& func, const int line);

}  // namespace assert_internal

}  // namespace match_stick


#ifdef _DEBUG

//! @brief エラーが発生したときにエラーメッセージを表示する．
//! @param expression エラーが発生条件の式(文字列)
//! @param error_mes エラーメッセージ．
#define MATCH_STICK_INTERNAL_ERROR_MESSAGE(expression, error_mes) \
const std::source_location location = std::source_location::current(); \
::match_stick::assert_internal::ErrorAssert(expression, error_mes, location.file_name(), \
    location.function_name(), location.line());

//! @brief エラーが発生したときにエラーメッセージを表示する．
//! @param expr エラーが発生したかどうかの条件．
//! @param error_mes エラーメッセージ．
#define ASSERT(expr, error_mes)                                     \
do {                                                                \
    if (!(expr)) {                                                  \
        const std::string expr_str = #expr;                         \
        const std::string message = error_mes;                      \
        MATCH_STICK_INTERNAL_ERROR_MESSAGE(expr_str, message);      \
    }                                                               \
} while (0)

#define ASSERT_NOT_NULL_PTR(ptr) ASSERT(ptr != nullptr, "nullptr passed.")

#define ASSERT_MUST_NOT_REACH_HERE() ASSERT(false, "This part is never reached.")

#else

#define ERROR_ASSERT(error_mes) ((void)0)

#define ASSERT(expr, error_mes) ((void)0)

#define ASSERT_NOT_NULL_PTR(ptr) ((void)0)

#define ASSERT_MUST_NOT_REACH_HERE() ((void)0)

#endif  // _DEBUG
