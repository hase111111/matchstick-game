
#pragma once

#include <memory>
#include <string>

#include "game_setting_record.h"


namespace match_stick {

class GameSettingImporter final {
public:
    GameSettingImporter() = default;
    ~GameSettingImporter() = default;

    std::shared_ptr<GameSettingRecord> import(const std::string & file_path) const;
};

}  // namespace match_stick
