
#pragma once

#include <functional>
#include <memory>
#include <string>

#include "dxlib_resource_loader.h"
#include "language_record.h"
#include "i_dxlib_user_interface.h"
#include "i_entity.h"


namespace match_stick {

class SimpleBoxButton final : public IDxLibUserInterface, public IEntity {
public:
    SimpleBoxButton(const std::shared_ptr<const LanguageRecord>& language_record,
                    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader,
                    const int center_x, const int center_y, const int width, const int height,
                    const std::string& text_key,
                    const std::string& font_name,
                    const std::function<void()>& callback_when_clicked);
    ~SimpleBoxButton() = default;

    bool isHovered(const int mouse_x, const int mouse_y) const override;

    void initHoverState(bool is_hovered) override;

    void callbackWhenClicked() override;

    void callbackWhenHoverStarted() override;

    void callbackWhenHoverEnded() override;

    constexpr bool update() override {
        return true;
    };

    void draw() const override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

private:
    const int font_handle_;
    const int click_sound_handle_;
    const int hover_sound_handle_;

    const int center_x_;
    const int center_y_;
    const int width_;
    const int height_;

    const std::string text_;

    const std::function<void()> callback_when_clicked_;

    bool is_hovered_ = false;
};

}  // namespace match_stick
