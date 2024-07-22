
#pragma once

#include <string>

#include <Windows.h>


namespace match_stick {

namespace assert_internal {

void ErrorAssert(const std::string& error_mes,
                 const LPCSTR file, const LPCSTR func, const int line);

}  // namespace assert_internal

}  // namespace match_stick


#ifdef _DEBUG

//! @brief エラーが発生したときにエラーメッセージを表示する．
//! @param error_mes エラーメッセージ．
#define ERROR_MESSAGE(error_mes) \
::match_stick::assert_internal::ErrorAssert(error_mes, __FILE__, __FUNCTION__, __LINE__)

//! @brief エラーが発生したときにエラーメッセージを表示する．
//! @param expr エラーが発生したかどうかの条件．
//! @param error_mes エラーメッセージ．
#define ASSERT(expr, error_mes)                                     \
do {                                                                \
    if (!(expr)) {                                                  \
        std::string message = "Assertion failed : ";                \
        message += #expr;                                           \
        message += "\n";                                            \
        message += error_mes;                                       \
        ERROR_MESSAGE(message);                                     \
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
