
#include "entity_updater.h"

#include <algorithm>
#include <string>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"

namespace match_stick {

void EntityUpdater::registerEntity(const std::shared_ptr<IEntity>& entity_ptr) {
    ASSERT(entity_ptr != nullptr, "entity_ptr is nullptr");

    entities_.push_back(entity_ptr);
}

void EntityUpdater::update() {
    // entityの updateを呼び出す，falseを返した entity は削除する
    for (size_t i = 0; i < entities_.size(); ++i) {
        if (!entities_[i]->update()) {
            entities_.erase(entities_.begin() + i);
            --i;
        }
    }

    // 10秒に1回デバッグメッセージを出力
    if (debug_counter_ % 600 == 0) {
        std::string debug_message = "EntityUpdater::update() entities_.size() : " +
            std::to_string(entities_.size());
        DEBUG_PRINT(debug_message);
    }

    // デバッグ用のカウンタをインクリメント
    ++debug_counter_;
}

void EntityUpdater::draw() const {
    // レイヤー順にソート
    std::vector<std::shared_ptr<IEntity>> sorted_entities_(entities_);

    auto sort_func = [](const std::shared_ptr<const IEntity>& a, const std::shared_ptr<const IEntity>& b) { return a->getLayer() < b->getLayer(); };

    std::sort(sorted_entities_.begin(), sorted_entities_.end(), sort_func);

    for (const auto& renderable : sorted_entities_) {
        renderable->draw();
    }
}

}  // namespace match_stick
