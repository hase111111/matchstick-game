
//! @file system_main.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https ://opensource.org/licenses/mit-license.php

#pragma once

#include <memory>
#include <string>

#include "game_setting_record.h"

namespace match_stick {

//! @class SystemMain
//! @brief ゲームの初期化・メインループ・終了処理を行うクラス．
class SystemMain final {
public:
    SystemMain() = default;
    ~SystemMain() = default;

    //! @brief ゲームの初期化処理を行う．
    //! 失敗した場合は即座に終了すること．
    //! @return 初期化に成功した場合は true，失敗した場合は false を返す．
    bool initialize();

    //! @brief ゲームの終了処理を行う．
    void finalize() const;

    //! @brief ゲームのメインループを実行する．
    void main() const;

private:
    static constexpr std::string kWindowClassName{ "DxLibMatchStickGameWindowClassName" };

    std::shared_ptr<GameSettingRecord> game_setting_record_ptr_;
};

}  // namespace match_stick
