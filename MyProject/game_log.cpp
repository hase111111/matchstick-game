
#include "game_log.h"

#include <DxLib.h>

#include "game_const.h"

namespace match_stick {

GameLog::GameLog(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                 const std::shared_ptr<FontLoader>& font_loader) :
    small_font_handle_(0) {}

void GameLog::draw() const {

    int _centerx = (GameConst::kResolutionX * 23 / 32 + GameConst::kResolutionX) / 2;
    int temp = 0;
    std::string temp_str = "";
    //盤面状況のアナウンス
    {
        temp = GetDrawStringWidthToHandle("=現在の盤面=", 13, small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 3 / 64, GetColor(0, 0, 0), small_font_handle_, "=現在の盤面=");
    }

    //ターン
    {
        temp_str = std::to_string(0) + "ターン目";
        if (true) { temp_str += " あなたの番です"; } else { temp_str += " あいての番です"; }
        temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 7 / 64, GetColor(0, 0, 0), small_font_handle_, temp_str.c_str());
    }

    //盤面状況
    {
        if (true) { temp_str = "あなた(先手)[" + std::to_string(0) + "," + std::to_string(0) + "]"; } else { temp_str = "あなた(後手)[" + std::to_string(0) + "," + std::to_string(0) + "]"; }
        if (true) { temp_str += ",采配残り" + std::to_string(0); }
        temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 12 / 64, GetColor(0, 0, 0), small_font_handle_, temp_str.c_str());

        if (true) { temp_str = "あいて(後手) [" + std::to_string(0) + "," + std::to_string(0) + "]"; } else { temp_str = "あいて(先手) [" + std::to_string(0) + "," + std::to_string(0) + "]"; }
        if (true) { temp_str += ",采配残り" + std::to_string(0); }
        temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 15 / 64, GetColor(0, 0, 0), small_font_handle_, temp_str.c_str());
    }

    //特殊ルール
    {
        temp_str = "MOD 5 ルール...";
        if (true) { temp_str += "あり"; } else { temp_str += "なし"; }
        temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 21 / 64, GetColor(0, 0, 0), small_font_handle_, temp_str.c_str());

        temp_str = "自傷 ルール...";
        if (true) { temp_str += "あり"; } else { temp_str += "なし"; }
        temp = GetDrawStringWidthToHandle(temp_str.c_str(), (int)temp_str.size(), small_font_handle_);
        DrawFormatStringToHandle(_centerx - temp / 2, GameConst::kResolutionY * 24 / 64, GetColor(0, 0, 0), small_font_handle_, temp_str.c_str());
    }
}

}  // namespace match_stick
