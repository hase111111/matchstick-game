
#pragma once

#include <map>
#include <string>

#include "language_record.h"

namespace match_stick {

class FontLoader final {
    using Country = LanguageRecord::Country;

public:
    int loadAndGetFontHandle(Country country, const std::string& file_path, int edge = 0);

    int getFontHandle(Country country, const std::string& file_path);

    void loadFontHandle(Country country, const std::string& file_path, int edge = 0);

private:
    static constexpr int kMaxFontHandleNum = 20;  //! フォントの読み込みの最大数を設定する．

    bool isCountryForOtherLanguage(Country country) const;

    bool alreadyLoadedFont(Country country, const std::string& file_path) const;

    int getFontSizeByString(const std::string& file_path) const;

    std::map<std::string, int> font_handle_;  //!< フォントを格納する配列．キーはファイルパス．

    //! 文字が存在しない中国語やハングルなどの文字を表示するためのフォントを格納する配列．
    std::map<std::string, int> font_handle_for_other_language_;
};

}  // namespace match_stick
