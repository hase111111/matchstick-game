
#pragma once

#include "game_setting_record.h"


namespace match_stick {

class GameSettingImporter final {
public:
    GameSettingImporter() = default;
    ~GameSettingImporter() = default;

    GameSettingRecord importSetting() const;
};

}  // namespace match_stick
