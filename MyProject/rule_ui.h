
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "font_loader.h"
#include "i_entity.h"
#include "rule_ui_hexagon.h"
#include "sound_effect_loader.h"

namespace match_stick {

class RuleUI final : public IEntity {
public:
    RuleUI(const std::shared_ptr<const DxLibInput>& input_ptr,
           const std::shared_ptr<FontLoader>& font_loader,
           const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);
    ~RuleUI() = default;

    inline int getLayer() const override {
        return constants::kUIBottomLayer;
    }

    bool update() override;

    void draw() const override;

private:
    RuleUIHexagon rule_ui_hexagon_;
};

}  // namespace match_stick
