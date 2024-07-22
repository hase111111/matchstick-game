
#include "dxlib_assert.h"

#include <DxLib.h>


void match_stick::assert_internal::ErrorAssert(
    const std::string& error_mes, const LPCSTR file,
    const LPCSTR func, const int line) {

    // エラーメッセージを表示する．
    clsDx();
    printfDx("Error! Please press the X button on the window to exit! \n\n");
    printfDx("<Error Cause>\n%s\n\n", error_mes.c_str());
    printfDx("File Name ： %s\n", file);
    printfDx("Function Name ： %s\n", func);
    printfDx("Lines ： %d\n", line);

    // 何もせずに待つ．
    while (!ProcessMessage()) {
        ClearDrawScreen();
        ScreenFlip();
    }

    DxLib_End();

    // プログラムを終了する．
    exit(99);
}
