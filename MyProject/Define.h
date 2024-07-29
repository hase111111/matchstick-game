
#pragma once

#include <string>

namespace match_stick {

class Define {
public:
    static const int WIN_SIZEX;
    static const int WIN_SIZEY;
    static const std::string WIN_TITLE;

    static const double WIN_EXRATE;

    static const double PI;
private:
    Define() = delete;
};

}  // namespace match_stick
