
#include "title_hand_animation.h"

#include <format>

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

TitleHandAnimation::TitleHandAnimation(const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    image_handle_(loadImages(dxlib_resource_loader_ptr)) {
    // 腕の画像のサイズを取得する
    GetGraphSize(image_handle_[0], &hand_size_x_, &hand_size_y_);

    initHandPos();
}

bool TitleHandAnimation::update() {
    const int random_range = 30;  // ベース座標から，-15～15ずれた座標に設置する

    // 全ての手を上へ移動させる & 画面外に行ったなら下へ戻す
    for (auto& i : hand_) {
        i.y -= i.v;

        // 腕の位置をリセットする処理
        if (i.y + hand_size_y_ / 2.0 < 0.0) {
            i.x = i.base_x + static_cast<double>(GetRand(random_range)) - random_range / 2.0;

            // 画面外に設置（0～腕2分程度ずらす）
            i.y = static_cast<double>(GameConst::kResolutionY) + hand_size_y_ / 2.0;

            // イラストはランダムに設定する
            i.graphic_index = static_cast<unsigned int>(GetRand(kImageNum - 1));

            // 速度を最大～最小に設定する，乱数で100等分して1.5～4.0にする
            i.v = Hand::kMinVelocity + (Hand::kMaxVelocity - Hand::kMinVelocity) *
                (GetRand(Hand::kVelocityDiscretization) / 100.0);
        }
    }

    return true;
}

void TitleHandAnimation::draw() const {
    for (const auto& i : hand_) {
        // 画面上部に行くほど透明になる
        const int blend = 150 - static_cast<int>(128 * (GameConst::kResolutionY - i.y) / GameConst::kResolutionY);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend);

        // 描画
        const int draw_x = static_cast<int>(i.x);
        const int draw_y = static_cast<int>(i.y);
        DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, image_handle_.at(i.graphic_index), TRUE);
    }

    SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

std::array<int, TitleHandAnimation::kImageNum> TitleHandAnimation::loadImages(
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) const {

    std::array<int, kImageNum> image_handle = {};

    for (unsigned int i = 0; i < kImageNum; ++i) {
        image_handle[i] = dxlib_resource_loader_ptr->getImageHandle(std::format("data/img/hand/{}_hand.png", i));
    }

    return image_handle;
}

void TitleHandAnimation::initHandPos() {
    const int hand_num = 10;  // 10個の腕を生成する

    // 腕を生成する
    for (int i = 0; i < hand_num; ++i) {
        Hand add;

        // 画面を十等分した座標を起点の座標として登録する
        add.x = add.base_x = static_cast<double>(GameConst::kResolutionX) / hand_num * i + (hand_size_x_ / 2.0) + 10;

        // 画面外に設置（0～腕6分程度ずらす）
        add.y = static_cast<double>(GameConst::kResolutionY) + hand_size_y_ / 2.0 +
            static_cast<double>(GetRand(hand_size_y_ * 6));

        // イラストはランダムに設定する
        add.graphic_index = static_cast<unsigned int>(GetRand(kImageNum - 1));

        // 速度を最大～最小に設定する，乱数で100等分して1.5～4.0にする
        add.v = Hand::kMinVelocity + (Hand::kMaxVelocity - Hand::kMinVelocity) *
            (GetRand(Hand::kVelocityDiscretization) / 100.0);

        hand_.push_back(add);  // 追加する
    }
}

}  // namespace match_stick
