#include "Sound.h"
#include "Error.h"
#include "DxLib.h"

int Sound::myLoadSound(std::string _path)
{
    if (m_soundeffect.count(_path) != 0) { return m_soundeffect[_path]; }

    const int temp_sound = LoadSoundMem(_path.c_str());

    if (temp_sound == -1) {
        std::string err_mes = "�T�E���h�G�t�F�N�g�̃��[�h���ł��܂���ł���\n�ǂݍ��݂Ɏ��s�����t�@�C�� : ";
        err_mes += _path;
        ERR(err_mes);
    }

    m_soundeffect[_path] = temp_sound;

    //���ʂ�ύX����
    ChangeVolumeSoundMem(255 * m_percent / 100, m_soundeffect[_path]);

    return m_soundeffect[_path];
}

void Sound::startBGM(std::string _path) {

//����BGM�̍Đ��󋵂𒲂ׂ�
    for (auto i = m_bgm.begin(); i != m_bgm.end(); ++i) {

        //�Đ����Ȃ��~����
        if (CheckSoundMem(i->second) == 1) {
            StopSoundMem(i->second);
        }
    }

//�ǂݍ��ݍς݂łȂ���΃��[�h����
    if (m_bgm.count(_path) == 0) {
        if ((m_bgm[_path] = LoadSoundMem(_path.c_str())) == -1) { 
            std::string err_mes = "���y�̃��[�h���ł��܂���ł���\n�ǂݍ��݂Ɏ��s�����t�@�C�� : ";
            err_mes += _path;
            ERR(err_mes);
        };

        //���ʂ�ύX����
        ChangeVolumeSoundMem(255 * m_percent / 100, m_bgm[_path]);
    }

//�Đ�����
    if (PlaySoundMem(m_bgm[_path], DX_PLAYTYPE_LOOP) == -1) {
        ERR("�y�Ȃ̍Đ����ł��܂���ł����B");
    };

//�Đ�����BGM�̃p�X���L�^����
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

    //BGM�̉��ʂ����ׂĕύX����
    for (auto i = m_bgm.begin(); i != m_bgm.end(); ++i) {
        ChangeVolumeSoundMem(255 * m_percent / 100, i->second);
    }

    //SE�̉��ʂ����ׂĕύX����
    for (auto i = m_soundeffect.begin(); i != m_soundeffect.end(); ++i) {
        ChangeVolumeSoundMem(255 * m_percent / 100, i->second);
    }
}
