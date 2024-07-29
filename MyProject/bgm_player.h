
#pragma once

#include <map>
#include <optional>
#include <string>

namespace match_stick {

class BgmPlayer final {
public:
    void load(const std::string& bgm_file);
    void play(const std::string& bgm_file);
    void loadAndPlay(const std::string& bgm_file);
    void stop();
    void changeVolume(int volume);

private:
    std::map<std::string, int> bgm_handle_;
    int volume_percent_{ 100 };

    std::optional<std::string> current_bgm_{ std::nullopt };
};

}  // namespace match_stick
