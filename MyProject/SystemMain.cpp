#include"DxLib.h"
#include"SystemMain.h"
#include"Define.h"
#include"Looper.h"
#include"Setting.h"
#include"Sound.h"

//DXライブラリやゲームの初期処理
bool SystemMain::initialize() const
{
    //icon.rcで設定したアイコンファイルをセットする
    SetWindowIconID(333);                                               

    SetWindowText(Define::WIN_TITLE.c_str());                           //ウィンドウタイトルを付ける
    SetAlwaysRunFlag(TRUE);                                             //ウィンドウがノンアクティブでも実行
    SetOutApplicationLogValidFlag(FALSE);                               //ログ出力しない
    const int COLOR_BIT = 32;                                           //色のbit数。通常32で良いが軽くするなら16にする
    SetGraphMode(Define::WIN_SIZEX, Define::WIN_SIZEY, COLOR_BIT);      //ゲーム画面の解像度を設定する

    Setting::getIns()->loadSettingFile();                               //セーブファイルを読み込む

    //音量を設定ファイル空設定する
    Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());

    //フルスクリーン設定
    if (Setting::getIns()->getSettingFulWin() == false) 
    {
        //ウィンドウモードで起動する場合
        ChangeWindowMode(TRUE);                                             //ウィンドウモードに変更
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);                        //ウィンドウサイズを自由に変更できるようにする

        //画面サイズ設定（スクリーンの大きさを取得して、それに合わせてウィンドウのサイズを変更する）
        RECT rc;
        GetWindowRect(GetDesktopWindow(), &rc);
        int width = rc.right - rc.left; //横幅取得
        double ex_rate = (double)width * Define::WIN_EXRATE / (double)Define::WIN_SIZEX;
        SetWindowSizeExtendRate(ex_rate);                                   //ウィンドウサイズを変更したい時はここに倍率を指定する
    }

    if (DxLib_Init()) {                         //DXライブラリ初期化処理
        return false;                           //異常終了したら即座にやめる
    }

    SetSysCommandOffFlag(TRUE);                 //ALTを無効にする
    SetDrawScreen(DX_SCREEN_BACK);              //裏画面処理を設定する

    return true;
}

//DXライブラリやゲームの終了処理
void SystemMain::finalize() const
{
    DxLib_End();
}

//メイン処理
void SystemMain::main() const
{
    Looper looper;
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }   
}
