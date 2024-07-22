
#include <DxLib.h>

#include "error_message_box.h"
#include "system_main.h"

int WINAPI WinMain(HINSTANCE h, HINSTANCE h_prev, LPSTR cmd, int cmd_show) {
    SystemMain system_main;

    if (system_main.initialize()) {
        system_main.main();
    }
    else {
        ErrorMessage::show("初期化に失敗しました。");
    }

    system_main.finalize();

    return 0;
}
