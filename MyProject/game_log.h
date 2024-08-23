
#pragma once

#include <memory>
#include <string>

#include "dxlib_resource_loader.h"
#include "i_entity.h"
#include "language_record.h"

namespace match_stick {

class GameLog final : public IEntity {
public:
    GameLog(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
            const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~GameLog() = default;

    inline int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    bool update() override {
        return true;
    }

    void draw() const override;

private:
    const int small_font_handle_;
};

}  // namespace match_stick
