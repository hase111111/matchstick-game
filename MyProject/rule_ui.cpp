
#include "rule_ui.h"

#include <cmath>

#include <DxLib.h>

#include "define.h"
#include "math_const.h"

namespace match_stick {

RuleUI::RuleUI(const std::shared_ptr<const DxLibInput>& input_ptr,
               const std::shared_ptr<FontLoader>& font_loader,
               const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr) :
    rule_ui_hexagon_(input_ptr, font_loader, sound_effect_loader_ptr) {}

bool RuleUI::update() {
    rule_ui_hexagon_.update();
    return true;
}

void RuleUI::draw() const {
    rule_ui_hexagon_.draw();
}

}  // namespace match_stick
