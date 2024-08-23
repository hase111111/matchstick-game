
#include "font_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

int FontLoader::getFontHandle(const Country country, const std::string& file_path) const {
    ASSERT(alreadyLoadedFont(country, file_path), "The font has not been loaded yet.");

    const int result_handle = isCountryForOtherLanguage(country) ?
        font_handle_for_other_language_.at(file_path) : font_handle_.at(file_path);

    ASSERT(result_handle >= 0, "Failed to get font handle. File Path : " + file_path);

    return result_handle;
}

void FontLoader::loadFontHandle(const Country country, const std::string& file_path) {
    // フォントをすでに読み込んでいるなら何もしない．
    if (alreadyLoadedFont(country, file_path)) {
        return;
    }

    // 読み込む．
    int font_handle = 0;

    if (isCountryForOtherLanguage(country)) {
        font_handle = CreateFontToHandle(NULL, getFontSizeByString(file_path), 2);
    } else {
        font_handle = LoadFontDataToHandle(file_path.c_str());
    }

    // assert内で読み込み処理をしてはいけないので注意．
    ASSERT(font_handle >= 0, "Failed to load font. File Path : " + file_path);

    // 読み込んだパスを記録する．
    if (isCountryForOtherLanguage(country)) {
        font_handle_for_other_language_[file_path] = font_handle;

        // 最大数を上回るならばエラーメッセージを表示する．
        ASSERT(font_handle_for_other_language_.size() <= kMaxFontHandleNum,
               "The number of loaded fonts exceeds the maximum number of fonts.");
    } else {
        font_handle_[file_path] = font_handle;

        // 最大数を上回るならばエラーメッセージを表示する．
        ASSERT(font_handle_.size() <= kMaxFontHandleNum,
               "The number of loaded fonts exceeds the maximum number of fonts.");
    }
}

bool FontLoader::isCountryForOtherLanguage(const Country country) const {
    return country == Country::kChinese || country == Country::kKorean;
}

bool FontLoader::alreadyLoadedFont(const Country country, const std::string& file_path) const {
    if (isCountryForOtherLanguage(country)) {
        return font_handle_for_other_language_.count(file_path) != 0;
    } else {
        return font_handle_.count(file_path) != 0;
    }
}

int FontLoader::getFontSizeByString(const std::string& file_path) const {
    // ex) azuki_font16.dft -> 16
    int font_size = 0;

    try {
        const std::string font_size_str = file_path.substr(file_path.size() - 6, 2);
        font_size = std::stoi(font_size_str);
    } catch (const std::exception&) {
        font_size = 16;
    }

    return font_size;
}

}  // namespace match_stick
