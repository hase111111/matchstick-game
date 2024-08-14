
#include "game_setting_exporter.h"

#include <string>

#include "toml_file_exporter.h"

namespace match_stick {

void GameSettingExporter::exportSetting(const GameSettingRecord& record) const {
    TomlFileExporter<GameSettingRecord> exporter;
    const std::string file_path = "game_setting.toml";

    exporter.Export(file_path, record);
}

}  // namespace match_stick
