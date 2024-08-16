
#pragma once

namespace match_stick {

class Define {
public:
    static constexpr int kWindowSizeX = 16 * 60;
    static constexpr int kWindowSizeY = 9 * 60;

    static constexpr char kWindowTitle[] = "Match Stick Game";

    static constexpr double kWindowExRate = 0.8;//0.625;
private:
    Define() = delete;
};

}  // namespace match_stick
