
#pragma once

#include <functional>
#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_entity.h"

namespace match_stick {

class TitleSceneSwitcher final : public IEntity {
public:
    TitleSceneSwitcher(const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                       const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr,
                       const std::function<void()>& scene_change_func);

    inline int getLayer() const override {
        return constants::kNoLayer;
    }

    bool update() override;

    void draw() const override {};

private:
    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    const std::function<void()> scene_change_func_;

    const int scene_change_sound_handle_;
};

}  // namespace match_stick
