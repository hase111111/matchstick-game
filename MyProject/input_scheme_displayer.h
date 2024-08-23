
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "i_entity.h"

namespace match_stick {

class InputSchemeDisplayer : public IEntity {
public:
    InputSchemeDisplayer(const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                         const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);

    inline int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;

private:
    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;

    const int keyboard_image_handle_;
    const int mouse_image_handle_;
};

}  // namespace match_stick
