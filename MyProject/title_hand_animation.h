
#pragma once

#include <array>
#include <memory>
#include <vector>

#include "i_entity.h"
#include "image_loader.h"

namespace match_stick {

class TitleHandAnimation final : public IEntity {
public:
    TitleHandAnimation(const std::shared_ptr<ImageLoader>& image_loader);
    ~TitleHandAnimation() = default;

    TitleHandAnimation& operator=(const TitleHandAnimation&) = delete;

    inline int getLayer() const override {
        return constants::kUIBottomLayer;
    }

    bool update() override;

    void draw() const override;

private:
    struct Hand final {
        static constexpr int kVelocityDiscretization = 100;
        static constexpr double kMaxVelocity = 4;
        static constexpr double kMinVelocity = 1.5;

        double base_x{ 0.0 };
        double x{ 0.0 };
        double y{ 0.0 };
        double v{ 3.0 };
        unsigned int graphic_index{ 0 };
    };

    static constexpr unsigned int kImageNum = 6;  //<! タイトル画面の手のアニメーション画像の数

    //! @brief タイトル画面の手のアニメーション画像をロードする
    std::array<int, kImageNum> loadImages(const std::shared_ptr<ImageLoader>& image_loader) const;

    void initHandPos();

    const std::array<int, kImageNum> image_handle_;  //<! タイトル画面の手のアニメーション画像のハンドル

    int hand_size_x_;  //!< グラフィックの横幅
    int hand_size_y_;  //!< グラフィックの縦幅

    std::vector<Hand> hand_;  //!< 手の座標や速度などの情報
};

}  // namespace match_stick
