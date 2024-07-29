
#pragma once

namespace match_stick {

class IUpdatableEntity {
public:
    virtual ~IUpdatableEntity() = default;

    virtual void update() = 0;
};

}  // namespace match_stick
