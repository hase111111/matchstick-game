﻿
#include "title_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

TitleBackGroundBase::TitleBackGroundBase(const std::shared_ptr<const ImageLoader>& image_loader) :
    image_handle_(image_loader->getImageHandle("data/img/title_back.png")) {}

void TitleBackGroundBase::draw() const {
    DrawRotaGraph(GameConst::kWindowSizeX / 2, GameConst::kWindowSizeY / 2, 1.0, 0.0, image_handle_, TRUE);
}

}  // namespace match_stick
