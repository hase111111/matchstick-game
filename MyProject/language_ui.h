﻿
#pragma once

#include <functional>
#include <memory>
#include <string>

#include "dxlib_input.h"
#include "font_loader.h"
#include "i_entity.h"
#include "language_record.h"
#include "image_loader.h"
#include "sound_effect_loader.h"

namespace match_stick {

class LanguageUI final : public IEntity {
public:
    LanguageUI(const std::shared_ptr<LanguageRecord>& language_record_ptr,
               const std::shared_ptr<const DxLibInput>& dxlib_input,
               const std::shared_ptr<FontLoader>& font_loader_ptr,
               const std::shared_ptr<ImageLoader>& img_loader_ptr,
               const std::shared_ptr<SoundEffectLoader>& sound_effect_loader,
               const std::function<void(bool)>& on_back_button_clicked);
    ~LanguageUI() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override;

    void draw() const override;

private:
    static constexpr int kIndexFirstValue = 1000000000;

    void updateSelectIndex();

    void updateDecideButton();

    void applyLanguage();

    void drawText() const;

    void drawButton() const;

    void drawTable() const;

    const std::shared_ptr<const DxLibInput> dxlib_input_;
    const std::shared_ptr<LanguageRecord> language_record_ptr_;

    int select_index_x_{ kIndexFirstValue }, select_index_y_{ kIndexFirstValue };

    bool now_scene_changed_{ false };

    LanguageRecord::Country current_country_;
    LanguageRecord::Country hovered_country_;
    const LanguageRecord::Country first_country_;

    const int font_handle_;
    const int button_font_handle_;
    const int small_font_handle_;

    const int select_sound_handle_;
    const int decide_sound_handle_;

    const int checked_img_handle_;

    const std::string button_reset_text_, button_back_text_, button_apply_back_text_;

    const std::function<void(bool)> on_back_button_clicked_;

    static_assert(kIndexFirstValue % 2 == 0, "kIndexFirstValue must be even number");
    static_assert(kIndexFirstValue % 4 == 0, "kIndexFirstValue must be multiple of 4");
};

}  // namespace match_stick
