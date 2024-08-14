
#pragma once

#include <memory>

#include "game_setting_record.h"


namespace match_stick {

class GameSettingExporter final {
public:
    GameSettingExporter() = default;
    ~GameSettingExporter() = default;

    void exportSetting(const GameSettingRecord& record) const;
};

}  // namespace match_stick
