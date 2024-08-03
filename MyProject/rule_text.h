
#pragma once

#include <memory>
#include <string>

#include "font_loader.h"

namespace match_stick {

class RuleText final {
public:
    RuleText(const std::shared_ptr<FontLoader>& font_loader);
    ~RuleText() = default;

    void update(int number);

    void draw() const;

private:
    void drawHexagon(int center_x, int center_y, int radius, bool fill, double angle_offset,
                     unsigned int edge_color, unsigned int fill_color) const;

    int getBoxLeft() const;
    int getBoxTop() const;
    int getBoxRight() const;
    int getBoxBottom() const;

    int counter_{ 0 };
    int number_{ 0 };

    const int font_handle_;

    const int box_left_;
    const int box_top_;
    const int box_right_;
    const int box_bottom_;
};

}  // namespace match_stick
