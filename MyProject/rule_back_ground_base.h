
#pragma once

#include <memory>

#include "i_entity.h"

namespace match_stick {

class RuleBackGroundBase final : public IEntity {
public:
    RuleBackGroundBase() = default;
    ~RuleBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;
};

}  // namespace match_stick
