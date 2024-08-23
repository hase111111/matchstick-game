
#pragma once

#include <map>
#include <string>

#include "dxlib_assert.h"

namespace match_stick {

//! @brief 画像を読み込むクラス．
class ImageLoader final {
public:
    void loadImageHandle(const std::string& file_path);

    [[nodiscard]]
    int getImageHandle(const std::string& file_path) const;

    void reloadAllImage();

private:
    [[nodiscard]]
    inline bool isImageLoaded(const std::string& file_path) const {
        return image_handle_.count(file_path) != 0;
    }

    std::map<std::string, int> image_handle_;  //!< 画像を格納する配列．キーはファイルパス．
};

}  // namespace match_stick
