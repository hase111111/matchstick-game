
#pragma once

#include <map>
#include <optional>
#include <string>

namespace match_stick {

class BgmPlayer final {
public:
    void loadBGM(const std::string& bgm_file);

    void playBGM(const std::string& bgm_file);

    void stopBGM();

    void changeAllVolume(int volume);

    [[nodiscard]]
    inline int getVolumePercent() const {
        return volume_percent_;
    }

private:
    [[nodiscard]]
    inline bool isLoaded(const std::string& file_path) const {
        return bgm_handle_.contains(file_path);
    }

    std::map<std::string, int> bgm_handle_;
    int volume_percent_{ 100 };

    std::optional<std::string> current_bgm_{ std::nullopt };
};

}  // namespace match_stick
