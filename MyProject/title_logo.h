
#pragma once

#include <memory>
#include <string>

#include "dxlib_input.h"
#include "font_loader.h"
#include "i_entity.h"
#include "language_record.h"

namespace match_stick {

class TitleLogo final : public IEntity {
public:
    TitleLogo(const std::shared_ptr<const DxLibInput>& input_ptr,
              const std::shared_ptr<const LanguageRecord>& language_record_ptr,
              const std::shared_ptr<FontLoader>& font_loader);
    ~TitleLogo();

    inline int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    bool update() override;

    void draw() const override;

private:
    const std::shared_ptr<const DxLibInput> input_ptr_;

    const int big_font_handle_;
    const int middle_font_handle_;
    const int small_font_handle_;

    const std::string game_title_;
    const std::string announce_keyboard_;
    const std::string announce_mouse_;
    const std::string copy_right_;

    const double blink_period_{ 30 };  //!< 点滅周期，単位はフレーム
    int counter_{ 0 };  //!< 点滅カウンタ
};

}  // namespace match_stick
