#include "Font.h"
#include "DxLib.h"
#include "Error.h"

int Font::getFontHandle(const std::string _path) {

    //�t�H���g�����łɓǂݍ���ł���Ȃ炻�̃n���h���𑗂�
    if (m_path.count(_path) != 0) {
        return m_path.at(_path);
    }

    //�ǂݍ���
    int _font;
    _font = LoadFontDataToHandle(_path.c_str());

    //�ǂݍ��݂Ɏ��s�����Ȃ�G���[���b�Z�[�W��\��
    if (_font == -1) { 
        std::string err_mes = "���ǂݍ��߂܂���ł���";
        err_mes = _path + err_mes;
        ERR(err_mes.c_str());
    }

    //�ǂݍ��񂾃p�X���L�^
    m_path[_path] = _font;

    //�ő吔������Ȃ�΃G���[���b�Z�[�W��\��
    if (m_path.size() > MAX_FONT_HANDLE_NUM) {
        std::string err_mes2 = "�t�H���g�̓ǂݍ��ݍő吔�F";
        err_mes2 += std::to_string(MAX_FONT_HANDLE_NUM);
        err_mes2 += "�����鐔�̃t�H���g���ǂݍ��܂�܂����B";
        ERR("");
    }

    return _font;
}
