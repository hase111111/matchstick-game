
#include "game_setting_importer.h"

#include "toml_file_importer.h"

namespace match_stick {

std::shared_ptr<GameSettingRecord> GameSettingImporter::import(const std::string & file_path) const {
    TomlFileImporter<GameSettingRecord> importer;

    auto record = importer.ImportOrUseDefault(file_path);

    return std::make_shared<GameSettingRecord>(record);
}

}  // namespace match_stick
