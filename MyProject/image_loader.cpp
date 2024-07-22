
#include "image_loader.h"

#include <DxLib.h>

#include "dxlib_assert.h"


namespace match_stick {

int ImageLoader::LoadAndGetImageHandle(const std::string& file_path) {

    // 既に読み込み済みならば，そのハンドルを返す．
    if (image_handle_.count(file_path) != 0) {
        return image_handle_[file_path];
    }

    // そうでなければ画像を読み込み，ハンドルを返す．
    const int graphic_handle = LoadGraph(file_path.c_str());

    // assert内で読み込み処理をしてはいけないので注意．
    ASSERT(graphic_handle >= 0, "Failed to load image. File Path : " + file_path);

    // 記録してから，ハンドルを返す．
    image_handle_[file_path] = graphic_handle;

    return graphic_handle;
}

}  // namespace match_stick
