
#pragma once

#include <memory>
#include <vector>

#include "i_dxlib_renderable.h"

namespace match_stick {

class DxLibRenderer final {
public:
    DxLibRenderer() = default;
    ~DxLibRenderer() = default;

    void Register(const std::shared_ptr<const IDxLibRenderable>& renderable_ptr);

    void Draw() const;

private:
    std::vector<std::shared_ptr<const IDxLibRenderable>> renderables_;
};

}  // namespace match_stick
