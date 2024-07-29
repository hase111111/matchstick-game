
#include "entity_updater.h"

namespace match_stick {

void EntityUpdater::registerEntity(const std::shared_ptr<IUpdatableEntity>& entity_ptr) {
    entities_.push_back(entity_ptr);
}

void EntityUpdater::update() {
    for (const auto& entity : entities_) {
        entity->update();
    }
}

}  // namespace match_stick
