
#pragma once

#include <memory>

#include "i_entity.h"
#include "image_loader.h"

namespace match_stick {

class GameBackGroundBase final : public IEntity {
public:
    GameBackGroundBase() = default;
    ~GameBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;
};

}  // namespace match_stick
