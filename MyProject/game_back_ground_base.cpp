
#include "game_back_ground_base.h"

#include <DxLib.h>

#include "define.h"

namespace match_stick {

void GameBackGroundBase::draw() const {
    // 背景は白い色
    DrawBox(0, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(255, 255, 255), TRUE);

    // ログの表示場所
    DrawBox(Define::WIN_SIZEX * 9 / 32, 0, 0, Define::WIN_SIZEY, GetColor(0xc3, 0xc3, 0xc3), TRUE);
    DrawBox(Define::WIN_SIZEX * 23 / 32, 0, Define::WIN_SIZEX, Define::WIN_SIZEY, GetColor(0xc3, 0xc3, 0xc3), TRUE);
}

}  // namespace match_stick
