
#pragma once

#include <memory>

#include "i_entity.h"
#include "image_loader.h"

namespace match_stick {

class TitleBackGroundBase final : public IEntity {
public:
    TitleBackGroundBase(const std::shared_ptr<const ImageLoader>& image_loader);
    ~TitleBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;

private:
    int image_handle_;  //<! 背景画像のハンドル
};

}  // namespace match_stick
