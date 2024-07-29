
#pragma once

#include <memory>

#include "i_dxlib_renderable.h"
#include "image_loader.h"

namespace match_stick {

class TitleBackGroundBase final : public IDxLibRenderable {
public:
    TitleBackGroundBase(const std::shared_ptr<ImageLoader>& image_loader);
    ~TitleBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    void Draw() const override;

private:
    int image_handle_;  //<! 背景画像のハンドル
};

}  // namespace match_stick
