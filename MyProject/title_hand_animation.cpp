
#include "title_hand_animation.h"

namespace match_stick {

TitleHandAnimation::TitleHandAnimation(const std::shared_ptr<ImageLoader>& image_loader) :
    image_handle_(loadImages(image_loader)) {
}

void TitleHandAnimation::update() {
}

void TitleHandAnimation::draw() const {
}

std::array<int, TitleHandAnimation::kImageNum> TitleHandAnimation::loadImages(const std::shared_ptr<ImageLoader>& image_loader) const {

    std::array<int, kImageNum> image_handle = {};

    for (int i = 0; i < kImageNum; ++i) {
        image_handle[i] = image_loader->LoadAndGetImageHandle("title/hand" + std::to_string(i) + ".png");
    }

    return image_handle;
}

}  // namespace match_stick
