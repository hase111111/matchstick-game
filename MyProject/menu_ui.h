
#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_entity.h"
#include "language_record.h"
#include "scene_name.h"

namespace match_stick {

class MenuUI final : public IEntity {
public:
    MenuUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
           const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
           const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr,
           const std::function<void()>& game_end_callback,
           const std::function<void()>& scene_back_callback,
           const std::function<void(SceneName)>& scene_change_callback);
    ~MenuUI() = default;

    inline int getLayer() const override {
        return constants::kUIMiddleLayer;
    }

    bool update() override;

    void draw() const override;

private:
    enum class BarType {
        kGameStart,
        kRule,
        kSetting,
        kReplay,
        kLanguage,
        kButton0,
        kButton1,
    };

    static constexpr int kBarWidth = 260;
    static constexpr int kBarHeight = 210;
    static constexpr int kBarThickness = 3;

    static constexpr int kBarStartX = 70;
    static constexpr int kBarStartY = 20;
    static constexpr int kBarDistance = 20;

    static constexpr int kButtonWidth = 200;
    static constexpr int kButtonHeight = 60;
    static constexpr int kButtonRight = 10;
    static constexpr int kButtonBottom = 10;

    static constexpr int kIndexMaxX = 3;
    static constexpr int kIndexMaxY = 3;

    void updateRotation();

    void updateSelectedBarType();

    BarType getBarTypeFromIndex() const;

    void drawBar() const;

    void drawButton() const;

    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    std::map<BarType, int> bar_image_handle_map_;
    std::map<BarType, double> bar_rotation_map_;
    std::map<BarType, std::string> bar_text_map_;

    const std::string button0_text_;
    const std::string button1_text_;

    BarType selected_bar_type_{ BarType::kGameStart };
    int selected_bar_index_x_{ 0 }, selected_bar_index_y_{ 0 };

    const int font_handle_{ 0 };
    const int big_font_handle_{ 0 };
    const int small_font_handle_{ 0 };

    const int sound_effect_handle_{ 0 };
    const int sound_effect_handle2_{ 0 };

    int counter_{ 0 };

    const std::function<void()> game_end_callback_;
    const std::function<void()> scene_back_callback_;
    const std::function<void(SceneName)> scene_change_callback_;
};

}  // namespace match_stick
