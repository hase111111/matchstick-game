
#include "game_back_ground_base.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

void GameBackGroundBase::draw() const {
    // 背景は白い色
    DrawBox(0, 0, GameConst::kResolutionX, GameConst::kResolutionY, GetColor(255, 255, 255), TRUE);

    // ログの表示場所
    const unsigned int color = GetColor(0xc3, 0xc3, 0xc3);
    DrawBox(GameConst::kResolutionX * 9 / 32, 0, 0, GameConst::kResolutionY, color, TRUE);
    DrawBox(GameConst::kResolutionX * 23 / 32, 0, GameConst::kResolutionX, GameConst::kResolutionY, color, TRUE);
}

}  // namespace match_stick
