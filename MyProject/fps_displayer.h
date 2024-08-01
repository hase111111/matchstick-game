
#pragma once

#include <memory>

#include "font_loader.h"
#include "fps_controller.h"
#include "i_entity.h"

namespace match_stick {

class FpsDisplayer final : public IEntity {
public:
    FpsDisplayer(const std::shared_ptr<const FpsController>& fps_controller_ptr,
                 const std::shared_ptr<FontLoader>& font_loader_ptr);

    ~FpsDisplayer() = default;

    inline int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;

private:
    const std::shared_ptr<const FpsController> fps_controller_ptr_;

    const int font_handle_;
};

}  // namespace match_stick
