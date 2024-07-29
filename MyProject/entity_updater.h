
#pragma once

#include <vector>
#include <memory>

#include "i_updatable_entity.h"

namespace match_stick {

class EntityUpdater final {
public:
    EntityUpdater() = default;
    ~EntityUpdater() = default;

    void registerEntity(const std::shared_ptr<IUpdatableEntity>& entity_ptr);
    void update();

private:
    std::vector<std::shared_ptr<IUpdatableEntity>> entities_;
};

}  // namespace match_stick
