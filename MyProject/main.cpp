
// C28251 を無視する
#pragma warning(disable: 28251)

#include <DxLib.h>

#include "dxlib_debug_print.h"
#include "error_message_box.h"
#include "system_main.h"

#include "match_game_sample.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    PREPAER_DEBUG_PRINT();

    using match_stick::ErrorMessageBox;
    using match_stick::SystemMain;

    SystemMain system_main;

    if (system_main.initialize()) {
        match_stick::MatchGameSample sample;
        sample.run();
        system_main.main();
    } else {
        ErrorMessageBox::show("初期化に失敗しました。");
    }

    system_main.finalize();

    return 0;
}
