
#include "Font.h"

#include <DxLib.h>

#include "dxlib_assert.h"

int Font::getFontHandle(const std::string _path) {

    //フォントをすでに読み込んでいるならそのハンドルを送る
    if (m_path.count(_path) != 0) {
        return m_path.at(_path);
    }

    //読み込む
    int _font;
    _font = LoadFontDataToHandle(_path.c_str());

    //読み込みに失敗したならエラーメッセージを表示
    if (_font == -1) {
        std::string err_mes = "が読み込めませんでした";
        err_mes = _path + err_mes;
        ASSERT(false, err_mes.c_str());
    }

    //読み込んだパスを記録
    m_path[_path] = _font;

    //最大数を上回るならばエラーメッセージを表示
    if (m_path.size() > MAX_FONT_HANDLE_NUM) {
        std::string err_mes2 = "フォントの読み込み最大数：";
        err_mes2 += std::to_string(MAX_FONT_HANDLE_NUM);
        err_mes2 += "を上回る数のフォントが読み込まれました。";
        ASSERT(false, err_mes2.c_str());
    }

    return _font;
}
