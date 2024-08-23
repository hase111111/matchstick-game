
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

    void updateRotation();

    void updateSelectedBarType();

    BarType getBarTypeFromIndex() const;

    void drawBar() const;

    void drawButton() const;

    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    std::map<BarType, int> bar_image_handle_map_;
    std::map<BarType, double> bar_rotation_map_;
    std::map<BarType, std::string> bar_text_map_;

    BarType selected_bar_type_{ BarType::kGameStart };
    int selected_bar_index_x_{ 0 }, selected_bar_index_y_{ 0 };

    int counter_{ 0 };

    const int font48_handle_{ 0 };
    const int font32_handle_{ 0 };
    const int font24_handle_{ 0 };

    const int select_sound_effect_handle_{ 0 };
    const int decision_sound_effect_handle_{ 0 };

    const std::string button0_text_;
    const std::string button1_text_;

    const std::function<void()> game_end_callback_;
    const std::function<void()> scene_back_callback_;
    const std::function<void(SceneName)> scene_change_callback_;
};

}  // namespace match_stick
