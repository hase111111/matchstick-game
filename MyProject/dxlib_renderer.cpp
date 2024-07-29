
#include "dxlib_renderer.h"

#include <algorithm>

#include <DxLib.h>

#include "dxlib_assert.h"

namespace match_stick {

void DxLibRenderer::registerRenderable(const std::shared_ptr<const IDxLibRenderable>& renderable_ptr) {
    ASSERT(renderable_ptr != nullptr, "renderable_ptr is nullptr");
    renderables_.push_back(renderable_ptr);
}

void DxLibRenderer::draw() const {
    // レイヤー順にソート
    std::vector<std::shared_ptr<const IDxLibRenderable>> sorted_renderables(renderables_);

    auto sort_func = [](const std::shared_ptr<const IDxLibRenderable>& a, const std::shared_ptr<const IDxLibRenderable>& b) { return a->getLayer() < b->getLayer(); };

    std::sort(sorted_renderables.begin(), sorted_renderables.end(), sort_func);

    // 描画する．
    for (const auto& renderable_ptr : sorted_renderables) {
        renderable_ptr->draw();
    }
}

}  // namespace match_stick
