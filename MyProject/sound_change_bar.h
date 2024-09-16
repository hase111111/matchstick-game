
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_dxlib_user_interface.h"
#include "i_entity.h"

namespace match_stick {

class SoundChangeBar final : public IDxLibUserInterface, public IEntity {
public:
    SoundChangeBar(
        const std::shared_ptr<const LanguageRecord>& language_record_ptr,
        const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
        const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr,
        int center_x,
        int center_y);
    ~SoundChangeBar() = default;

    bool update() override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    void draw() const override;

    bool isHovered(int mouse_x, int mouse_y) const;

    void initHoverState(bool is_hovered);

    void callbackWhenClicked();

    void callbackWhenHoverStarted();

    void callbackWhenHoverEnded();

private:
    void drawBar() const;

    const std::shared_ptr<const DxLibInput>& dxlib_input_ptr_;
    const std::shared_ptr<const DxLibResourceLoader> dxlib_resource_loader_ptr_;

    const int font32_handle_;

    const int center_x_;
    const int center_y_;

    const int triangle_width_{ 20 };
};

}  // match_stick
