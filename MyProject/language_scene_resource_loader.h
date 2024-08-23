
#pragma once

#include <memory>

#include "dxlib_resource_loader.h"

namespace match_stick {

class LanguageSceneResourceLoader final {
public:
    LanguageSceneResourceLoader(const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~LanguageSceneResourceLoader() = default;

    void loadImage();

private:
    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
