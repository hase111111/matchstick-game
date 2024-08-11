
#pragma once

#include <memory>

#include "define.h"
#include "dxlib_input.h"
#include "font_loader.h"
#include "i_entity.h"
#include "sound_effect_loader.h"

namespace match_stick {

class RuleUIHexagon final {
public:
    RuleUIHexagon(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                  const std::shared_ptr<const DxLibInput>& input_ptr,
                  const std::shared_ptr<FontLoader>& font_loader,
                  const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);
    ~RuleUIHexagon() = default;

    int update(bool hexagon_is_hovered);

    void draw() const;

private:
    void drawHexagon(int center_x, int center_y, int radius, bool fill,
                 unsigned int edge_color, unsigned int fill_color) const;

    int getHoverIndex(int x, int y) const;
    bool isInsideHexagon(int x, int y, int center_x, int center_y, int radius) const;

    const std::shared_ptr<const DxLibInput> input_ptr_;

    const int font_handle_;

    const int sound_effect1_handle_;
    const int sound_effect2_handle_;

    const int radius_{ 30 };
    const int hexagon_center_x_{ Define::kWindowSizeX / 24 };
    const int hexagon_center_y_{ Define::kWindowSizeY / 5 };
    const int hexagon_num_{ 14 };

    int current_pointing_{ 0 };
    int current_hover_{ -1 };

    int counter_{ 0 };
    int hover_counter_{ 0 };

    bool hexagon_is_hovered_{ false };
};

}  // namespace match_stick
