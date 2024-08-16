
#include "dxlib_assert.h"

#include <format>

#include <DxLib.h>

void match_stick::assert_internal::ErrorAssert(
    const std::string& conditional_expression,
    const std::string& error_mes, const std::string& file,
    const std::string& func, const int line) {

    // エラーメッセージを表示する．
    clsDx();
    printfDx("Error! Please press the X button on the window to exit! \n\n");
    printfDx("%s", std::format("Error Condition : {}\n\n", conditional_expression).c_str());
    printfDx("%s", std::format("Error Cause : {}\n\n", error_mes).c_str());
    printfDx("%s", std::format("File Name : {}\n\n", file).c_str());
    printfDx("%s", std::format("Function Name : {}\n\n", func).c_str());
    printfDx("%s", std::format("Line Number : {}\n\n", line).c_str());

    // 何もせずに待つ．
    while (!ProcessMessage()) {
        ClearDrawScreen();
        ScreenFlip();
    }

    DxLib_End();

    // プログラムを終了する．
    exit(99);
}
