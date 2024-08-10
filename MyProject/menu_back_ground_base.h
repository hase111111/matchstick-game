
#pragma once

#include <memory>

#include "i_entity.h"
#include "image_loader.h"

namespace match_stick {

class MenuBackGroundBase final : public IEntity {
public:
    MenuBackGroundBase() = default;
    ~MenuBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;
};

}  // namespace match_stick
