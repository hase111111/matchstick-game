
#pragma once

#include <memory>

#include "dxlib_resource_loader.h"

namespace match_stick {

class RuleSceneResourceLoader final {
public:
    RuleSceneResourceLoader(const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~RuleSceneResourceLoader() = default;

    void loadImage();

private:
    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
