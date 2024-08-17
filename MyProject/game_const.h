
#pragma once

namespace match_stick {

class GameConst {
public:
    static constexpr int kResolutionX = 960;
    static constexpr int kResolutionY = 540;

    static constexpr char kWindowTitle[] = "Match Stick Game";

    static constexpr double kWindowExRate = 0.8;//0.625;
private:
    GameConst() = delete;
};

}  // namespace match_stick
