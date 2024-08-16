
#include "entity_updater.h"

#include <algorithm>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "string_util.h"

namespace match_stick {

void EntityUpdater::registerEntity(const std::shared_ptr<IEntity>& entity_ptr) {
    ASSERT(entity_ptr != nullptr, "entity_ptr is nullptr");

    entities_.push_back(entity_ptr);

    DEBUG_PRINT_INFO("register entity. now stack size is " + std::to_string(entities_.size()));
}

void EntityUpdater::update() {
    // entityの updateを呼び出す，falseを返した entity は削除する
    for (size_t i = 0; i < entities_.size(); ++i) {
        ASSERT(i < entities_.size(), "index out of range");
        ASSERT(entities_[i] != nullptr, "entity is nullptr");

        if (!entities_[i]->update()) {
            entities_.erase(entities_.begin() + i);
            --i;

            DEBUG_PRINT_INFO("erase entity. now stack size is " + std::to_string(entities_.size()));
        }
    }
}

void EntityUpdater::draw() const {
    // レイヤー順にソート
    // もし Entity が多い場合は Entity 追加・削除時にソートして，その値を使いまわす設計に変更する
    std::vector<std::shared_ptr<IEntity>> sorted_entities_(entities_);

    auto sort_func = [](const std::shared_ptr<const IEntity>& a, const std::shared_ptr<const IEntity>& b) {
        return a->getLayer() < b->getLayer();
        };

    std::sort(sorted_entities_.begin(), sorted_entities_.end(), sort_func);

    // 描画
    for (const auto& renderable : sorted_entities_) {
        renderable->draw();
    }
}

}  // namespace match_stick
