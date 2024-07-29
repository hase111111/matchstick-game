
#pragma once

#include<string>

namespace match_stick {

class Define {
public:
    const static int WIN_SIZEX;
    const static int WIN_SIZEY;
    const static std::string WIN_TITLE;

    const static double WIN_EXRATE;

    const static double PI;
private:
    Define() = delete;
};

}  // namespace match_stick
