
#pragma once

#include <functional>
#include <memory>
#include <string>

#include "dxlib_input.h"
#include "font_loader.h"
#include "i_entity.h"
#include "language_record.h"
#include "rule_text.h"
#include "rule_ui_hexagon.h"
#include "sound_effect_loader.h"

namespace match_stick {

class RuleUI final : public IEntity {
public:
    RuleUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
           const std::shared_ptr<const DxLibInput>& input_ptr,
           const std::shared_ptr<FontLoader>& font_loader,
           const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr,
           std::function<void()> on_button_pressed);
    ~RuleUI() = default;

    inline int getLayer() const override {
        return constants::kUIBottomLayer;
    }

    bool update() override;

    void draw() const override;

private:
    void drawButton() const;
    bool isButtonHovered() const;
    void updateButton();

    const std::function<void()> on_button_pressed_;

    const std::shared_ptr<const DxLibInput> input_ptr_;
    RuleUIHexagon rule_ui_hexagon_;
    RuleText rule_text_;

    const int font_handle_;
    const int sound_effect1_handle_;
    const int sound_effect2_handle_;

    bool is_button_hovered_{ false };
    bool already_button_pressed_{ false };

    const std::string button_text_;
};

}  // namespace match_stick
