
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_entity.h"

namespace match_stick {

class RuleUIHexagon final {
public:
    RuleUIHexagon(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                  const std::shared_ptr<const DxLibInput>& input_ptr,
                  const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~RuleUIHexagon() = default;

    int update(bool hexagon_is_hovered);

    void draw() const;

private:
    void drawHexagon(int center_x, int center_y, int radius, bool fill,
                 unsigned int edge_color, unsigned int fill_color) const;

    int getHoverIndex(int x, int y) const;
    bool isInsideHexagon(int x, int y, int center_x, int center_y, int radius) const;

    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    const int font_handle_;

    const int sound_effect1_handle_;
    const int sound_effect2_handle_;

    int current_pointing_{ 0 };
    int current_hover_{ -1 };

    int counter_{ 0 };
    int hover_counter_{ 0 };

    bool hexagon_is_hovered_{ false };
};

}  // namespace match_stick
