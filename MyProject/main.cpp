
// C28251 を無視する
#pragma warning(disable: 28251)

#include <DxLib.h>

#include "error_message_box.h"
#include "system_main.h"


int WINAPI WinMain(HINSTANCE h, HINSTANCE h_prev, LPSTR cmd, int cmd_show) {

    using match_stick::ErrorMessageBox;
    using match_stick::SystemMain;

    SystemMain system_main;

    if (system_main.initialize()) {
        system_main.main();
    }
    else {
        ErrorMessageBox::show("初期化に失敗しました。");
    }

    system_main.finalize();

    return 0;
}
