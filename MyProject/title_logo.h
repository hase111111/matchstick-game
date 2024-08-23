
#pragma once

#include <memory>
#include <string>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_entity.h"
#include "language_record.h"

namespace match_stick {

class TitleLogo final : public IEntity {
public:
    TitleLogo(const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
              const std::shared_ptr<const LanguageRecord>& language_record_ptr,
              const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~TitleLogo() = default;

    inline int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    bool update() override;

    void draw() const override;

private:
    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    const int font64_handle_;
    const int font32_handle_;
    const int font20_handle_;

    const std::string game_title_;
    const std::string announce_keyboard_text_;
    const std::string announce_mouse_text_;
    const std::string copy_right_text_;

    const double blink_period_{ 30 };  //!< 点滅周期，単位はフレーム
    int counter_{ 0 };  //!< 点滅カウンタ
};

}  // namespace match_stick
