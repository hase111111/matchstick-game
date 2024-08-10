
#pragma once

#include "i_entity.h"

namespace match_stick {

class MenuUI final : public IEntity {
public:
    MenuUI() = default;
    ~MenuUI() = default;

    inline int getLayer() const override {
        return constants::kUIBottomLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;
};

}  // namespace match_stick
