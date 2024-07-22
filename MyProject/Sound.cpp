
#include <DxLib.h>

#include "error.h"
#include "sound.h"

int Sound::myLoadSound(std::string _path)
{
    if (m_soundeffect.count(_path) != 0) { return m_soundeffect[_path]; }

    const int temp_sound = LoadSoundMem(_path.c_str());

    if (temp_sound == -1) {
        std::string err_mes = "サウンドエフェクトのロードができませんでした\n読み込みに失敗したファイル : ";
        err_mes += _path;
        ERR(err_mes);
    }

    m_soundeffect[_path] = temp_sound;

    //音量を変更する
    ChangeVolumeSoundMem(255 * m_percent / 100, m_soundeffect[_path]);

    return m_soundeffect[_path];
}

void Sound::startBGM(std::string _path) {

    //他のBGMの再生状況を調べる
    for (auto i = m_bgm.begin(); i != m_bgm.end(); ++i) {

        //再生中なら停止する
        if (CheckSoundMem(i->second) == 1) {
            StopSoundMem(i->second);
        }
    }

    //読み込み済みでなければロードする
    if (m_bgm.count(_path) == 0) {
        if ((m_bgm[_path] = LoadSoundMem(_path.c_str())) == -1) {
            std::string err_mes = "音楽のロードができませんでした\n読み込みに失敗したファイル : ";
            err_mes += _path;
            ERR(err_mes);
        };

        //音量を変更する
        ChangeVolumeSoundMem(255 * m_percent / 100, m_bgm[_path]);
    }

    //再生する
    if (PlaySoundMem(m_bgm[_path], DX_PLAYTYPE_LOOP) == -1) {
        ERR("楽曲の再生ができませんでした。");
    };

    //再生中のBGMのパスを記録する
    m_playbgm = _path;
}

void Sound::stopBGM() {
    StopSoundMem(m_bgm[m_playbgm]);
}

void Sound::changeVolume(const int percent)
{
    m_percent = percent;
    if (m_percent > 100) { m_percent = 100; }
    if (m_percent < 0) { m_percent = 0; }

    //BGMの音量をすべて変更する
    for (auto i = m_bgm.begin(); i != m_bgm.end(); ++i) {
        ChangeVolumeSoundMem(255 * m_percent / 100, i->second);
    }

    //SEの音量をすべて変更する
    for (auto i = m_soundeffect.begin(); i != m_soundeffect.end(); ++i) {
        ChangeVolumeSoundMem(255 * m_percent / 100, i->second);
    }
}
