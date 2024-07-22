
#pragma once

#include <map>
#include <string>

namespace match_stick {

class FontLoader final {
public:
    int LoadAndGetFontHandle(const std::string& file_path, int edge = 0);

private:
    static constexpr int kMaxFontHandleNum = 10;  //! フォントの読み込みの最大数を設定する．

    std::map<std::string, int> font_handle_;  //!< フォントを格納する配列．キーはファイルパス．
};

}  // namespace match_stick
