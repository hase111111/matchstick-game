
#include <DxLib.h>

#include "system_main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SystemMain system_main;

    if (system_main.initialize()) {
        system_main.main();
    }
    else {
        MessageBox(NULL, TEXT("関数:DxLibInitがエラーを起こしたため\n緊急終了しました。\nP.S このアプリは二重起動できません"), TEXT("報告"), MB_ICONERROR);
    }

    system_main.finalize();

    return 0;
}