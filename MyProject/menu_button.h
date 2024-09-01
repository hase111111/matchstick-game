
#pragma once

#include <functional>
#include <memory>
#include <string>

#include "dxlib_resource_loader.h"
#include "language_record.h"
#include "i_dxlib_user_interface.h"
#include "i_entity.h"

namespace match_stick {

class MenuButton final : public IDxLibUserInterface, public IEntity {
public:
    MenuButton(const std::shared_ptr<const LanguageRecord>& language_record,
               const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader,
               int center_x, int center_y,
               const std::string& icon_path,
               const std::string& text_key,
               const std::function<void()>& callback_when_clicked,
               bool is_large_button = false);
    ~MenuButton() = default;

    bool isHovered(const int mouse_x, const int mouse_y) const override;

    void initHoverState(bool is_hovered) override;

    void callbackWhenClicked() override;

    void callbackWhenHoverStarted() override;

    void callbackWhenHoverEnded() override;

    bool update() override;

    void draw() const override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

private:
    const int font_handle_;
    const int icon_image_handle_;
    const int click_sound_handle_;
    const int hover_sound_handle_;

    const int center_x_;
    const int center_y_;
    const int width_;
    const int height_;

    const int button_thickness_{ 3 };
    const unsigned int button_base_color_;
    const unsigned int button_hovered_color_;
    const unsigned int button_frame_color_;
    const unsigned int button_text_color_;

    const std::string text_;

    const std::function<void()> callback_when_clicked_;

    const bool is_large_button_;

    bool is_hovered_ = false;

    double icon_rotation_{ 0.0 };
};

}  // namespace match_stick
