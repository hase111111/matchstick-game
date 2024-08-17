
#pragma once

namespace match_stick {

class GameConst {
public:
    static constexpr int kWindowSizeX = 960;
    static constexpr int kWindowSizeY = 540;

    static constexpr char kWindowTitle[] = "Match Stick Game";

    static constexpr double kWindowExRate = 0.8;//0.625;
private:
    GameConst() = delete;
};

}  // namespace match_stick
