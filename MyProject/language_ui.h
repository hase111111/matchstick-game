
#pragma once

#include "i_entity.h"

namespace match_stick {

class LanguageUI final : public IEntity {
public:
    LanguageUI() = default;
    ~LanguageUI() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override;

    void draw() const override;
};

}  // namespace match_stick
