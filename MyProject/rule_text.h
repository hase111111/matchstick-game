
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "dxlib_resource_loader.h"
#include "language_record.h"

namespace match_stick {

class RuleText final {
public:
    RuleText(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
        const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~RuleText() = default;

    void update(int number);

    void draw() const;

private:
    void updateDrawText();

    void drawHexagon(int center_x, int center_y, int radius, bool fill, double angle_offset,
        unsigned int edge_color, unsigned int fill_color) const;

    void drawNumberBox() const;

    void drawText() const;

    std::vector<std::vector<std::string>> createRuleText(
        const std::shared_ptr<const LanguageRecord>& language_record_ptr) const;

    int getBoxLeft() const;
    int getBoxTop() const;
    int getBoxRight() const;
    int getBoxBottom() const;

    const LanguageRecord::Country current_country_;

    int counter_{ 0 };
    int number_{ 0 };

    std::vector<std::string> draw_text_{};

    const std::vector<std::vector<std::string>> rule_text_;

    const bool need_hyphen_;

    double hexagon_angle_velocity_{ 0 };

    const int font32_handle_;
    const int font24_handle_;

    const int box_left_;
    const int box_top_;
    const int box_right_;
    const int box_bottom_;
};

}  // namespace match_stick
