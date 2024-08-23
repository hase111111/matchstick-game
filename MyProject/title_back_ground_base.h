
#pragma once

#include <memory>

#include "dxlib_resource_loader.h"
#include "i_entity.h"

namespace match_stick {

class TitleBackGroundBase final : public IEntity {
public:
    TitleBackGroundBase(const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~TitleBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;

private:
    const int image_handle_;  //<! 背景画像のハンドル
};

}  // namespace match_stick
