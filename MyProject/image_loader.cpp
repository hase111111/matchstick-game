
#include "image_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

void ImageLoader::loadImageHandle(const std::string& file_path) {
    // 既に読み込み済みならば，そのハンドルを返す．
    if (image_handle_.contains(file_path)) {
        return;
    }

    // そうでなければ画像を読み込み，ハンドルを返す．
    const int graphic_handle = LoadGraph(file_path.c_str());

    // assert内で読み込み処理をしてはいけないので注意．
    ASSERT(graphic_handle >= 0, "Failed to load image. File Path : " + file_path);

    // 記録してから，ハンドルを返す．
    image_handle_[file_path] = graphic_handle;

    return;
}

int ImageLoader::getImageHandle(const std::string& file_path) const {
    ASSERT(isImageLoaded(file_path), "The image is not loaded. File is " + file_path);
    return image_handle_.at(file_path);
}

void ImageLoader::reloadAllImage() {
    // すべての画像を解放する．
    InitGraph();

    // ハンドルを -1 にする．
    for (auto& pair : image_handle_) {
        pair.second = -1;
    }

    // すべての画像を再読み込みする．
    for (auto& pair : image_handle_) {
        pair.second = LoadGraph(pair.first.c_str());
        ASSERT(pair.second >= 0, "Failed to reload image. File Path : " + pair.first);
    }
}

}  // namespace match_stick
