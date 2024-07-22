
#pragma once

#include <map>
#include <optional>
#include <string>

namespace match_stick {

class BgmPlayer final {
public:
    void Load(const std::string& bgm_file);
    void Play(const std::string& bgm_file);
    void LoadAndPlay(const std::string& bgm_file);
    void Stop();
    void ChangeVolume(int volume);

private:
    std::map<std::string, int> bgm_handle_;
    int volume_percent_{ 100 };

    std::optional<std::string> current_bgm_{ std::nullopt };
};

}  // namespace match_stick
