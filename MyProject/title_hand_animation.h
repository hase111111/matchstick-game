
#pragma once

#include <array>
#include <memory>

#include "i_dxlib_renderable.h"
#include "i_updatable_entity.h"
#include "image_loader.h"

namespace match_stick {

class TitleHandAnimation final : public IDxLibRenderable, public IUpdatableEntity {
public:
    TitleHandAnimation(const std::shared_ptr<ImageLoader>& image_loader);
    ~TitleHandAnimation() = default;

    inline int getLayer() const override {
        return constants::kUIBottomLayer;
    }

    void update() override;

    void draw() const override;

private:
    static constexpr int kImageNum = 6;  //<! タイトル画面の手のアニメーション画像の数

    std::array<int, kImageNum> loadImages(const std::shared_ptr<ImageLoader>& image_loader) const;

    const std::array<int, kImageNum> image_handle_;  //<! タイトル画面の手のアニメーション画像のハンドル
};

}  // namespace match_stick
