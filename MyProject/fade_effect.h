
#pragma once

#include <functional>
#include <vector>

#include "i_dxlib_renderable.h"
#include "i_updatable_entity.h"

namespace match_stick {

class FadeEffect final : public IDxLibRenderable, public IUpdatableEntity {
public:
    enum class FadeType {
        kFadeIn,
        kFadeOut,
    };

    FadeEffect(int fade_time, FadeType fade_type, std::function<void()> callback);
    ~FadeEffect() = default;

    inline int getLayer() const override {
        return constants::kFrontLayer;
    }

    void update() override;

    void draw() const override;

private:
    const int fade_time_;
    const FadeType fade_type_;
    const std::function<void()> callback_;

    int counter_{ 0 };
};

}  // namespace match_stick
