#include"DxLib.h"
#include"SystemMain.h"
#include"Define.h"
#include"Looper.h"
#include"Setting.h"
#include"Sound.h"

//DX���C�u������Q�[���̏�������
bool SystemMain::initialize() const
{
    //icon.rc�Őݒ肵���A�C�R���t�@�C�����Z�b�g����
    SetWindowIconID(333);                                               

    SetWindowText(Define::WIN_TITLE.c_str());                           //�E�B���h�E�^�C�g����t����
    SetAlwaysRunFlag(TRUE);                                             //�E�B���h�E���m���A�N�e�B�u�ł����s
    SetOutApplicationLogValidFlag(FALSE);                               //���O�o�͂��Ȃ�
    const int COLOR_BIT = 32;                                           //�F��bit���B�ʏ�32�ŗǂ����y������Ȃ�16�ɂ���
    SetGraphMode(Define::WIN_SIZEX, Define::WIN_SIZEY, COLOR_BIT);      //�Q�[����ʂ̉𑜓x��ݒ肷��

    Setting::getIns()->loadSettingFile();                               //�Z�[�u�t�@�C����ǂݍ���

    //���ʂ�ݒ�t�@�C����ݒ肷��
    Sound::getIns()->changeVolume(Setting::getIns()->getSettingVol());

    //�t���X�N���[���ݒ�
    if (Setting::getIns()->getSettingFulWin() == false) 
    {
        //�E�B���h�E���[�h�ŋN������ꍇ
        ChangeWindowMode(TRUE);                                             //�E�B���h�E���[�h�ɕύX
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);                        //�E�B���h�E�T�C�Y�����R�ɕύX�ł���悤�ɂ���

        //��ʃT�C�Y�ݒ�i�X�N���[���̑傫�����擾���āA����ɍ��킹�ăE�B���h�E�̃T�C�Y��ύX����j
        RECT rc;
        GetWindowRect(GetDesktopWindow(), &rc);
        int width = rc.right - rc.left; //�����擾
        double ex_rate = (double)width * Define::WIN_EXRATE / (double)Define::WIN_SIZEX;
        SetWindowSizeExtendRate(ex_rate);                                   //�E�B���h�E�T�C�Y��ύX���������͂����ɔ{�����w�肷��
    }

    if (DxLib_Init()) {                         //DX���C�u��������������
        return false;                           //�ُ�I�������瑦���ɂ�߂�
    }

    SetSysCommandOffFlag(TRUE);                 //ALT�𖳌��ɂ���
    SetDrawScreen(DX_SCREEN_BACK);              //����ʏ�����ݒ肷��

    return true;
}

//DX���C�u������Q�[���̏I������
void SystemMain::finalize() const
{
    DxLib_End();
}

//���C������
void SystemMain::main() const
{
    Looper looper;
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
        if (!looper.loop()) {
            break;
        }
    }   
}
