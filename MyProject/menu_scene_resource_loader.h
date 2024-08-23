
#pragma once

#include <memory>

#include "dxlib_resource_loader.h"

namespace match_stick {

class MenuSceneResourceLoader final {
public:
    MenuSceneResourceLoader(const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~MenuSceneResourceLoader() = default;

    void loadImage();

private:
    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
