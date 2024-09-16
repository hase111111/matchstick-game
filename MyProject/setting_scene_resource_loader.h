
#pragma once

#include <memory>

#include "dxlib_resource_loader.h"

namespace match_stick {

class SettingSceneResourceLoader final {
public:
    explicit SettingSceneResourceLoader(const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~SettingSceneResourceLoader() = default;

    void load();

private:
    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
