
#pragma once

#include <memory>

#include "i_entity.h"

namespace match_stick {

class SettingBackGroundBase final : public IEntity {
public:
    SettingBackGroundBase() = default;
    ~SettingBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;
};

}  // namespace match_stick
