
#pragma once

#include <functional>
#include <memory>

#include "dxlib_input.h"
#include "i_entity.h"
#include "sound_effect_loader.h"

namespace match_stick {

class TitleSceneSwitcher final : public IEntity {
public:
    TitleSceneSwitcher(const std::shared_ptr<const DxLibInput>& input_ptr,
                       const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr,
                       const std::function<void()>& scene_change_func);

    inline int getLayer() const override {
        return constants::kNoLayer;
    }

    bool update() override;

    void draw() const override {};

private:
    const std::shared_ptr<const DxLibInput> input_ptr_;

    const std::function<void()> scene_change_func_;

    const int scene_change_sound_handle_;
};

}  // namespace match_stick