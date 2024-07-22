
#include "font_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

int FontLoader::LoadAndGetFontHandle(const std::string& file_path, const int edge) {

    // フォントをすでに読み込んでいるならそのハンドルを返す．
    if (font_handle_.count(file_path) != 0) {
        return font_handle_.at(file_path);
    }

    // 読み込む．
    int font_handle;
    font_handle = LoadFontDataToHandle(file_path.c_str(), edge);

    ASSERT(font_handle >= 0, "Failed to load font. File Path : " + file_path);  // assert内で読み込み処理をしてはいけないので注意．

    // 読み込んだパスを記録する．
    font_handle_[file_path] = font_handle;

    // 最大数を上回るならばエラーメッセージを表示する．
    ASSERT(font_handle_.size() <= kMaxFontHandleNum, "The number of loaded fonts exceeds the maximum number of fonts.");

    return font_handle_.at(file_path);;
}

}  // namespace match_stick
