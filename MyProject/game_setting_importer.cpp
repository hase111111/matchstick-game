
#include "game_setting_importer.h"

#include <string>

#include "toml_file_importer.h"

namespace match_stick {

GameSettingRecord GameSettingImporter::importSetting() const {
    TomlFileImporter<GameSettingRecord> importer;
    const std::string file_path = "game_setting.toml";

    auto record = importer.ImportOrUseDefault(file_path);

    return record;
}

}  // namespace match_stick
