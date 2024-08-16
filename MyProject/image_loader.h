
#pragma once

#include <map>
#include <string>

#include "dxlib_assert.h"

namespace match_stick {

//! @brief 画像を読み込むクラス．
class ImageLoader final {
public:
    int loadAndGetImageHandle(const std::string& file_path);

    inline int getImageHandle(const std::string& file_path) const {
        ASSERT(isImageLoaded(file_path), "The image is not loaded. File is " + file_path);
        return image_handle_.at(file_path);
    }

    inline bool isImageLoaded(const std::string& file_path) const {
        return image_handle_.count(file_path) != 0;
    }

    void reloadAllImage();
private:
    std::map<std::string, int> image_handle_;  //!< 画像を格納する配列．キーはファイルパス．
};

}  // namespace match_stick
