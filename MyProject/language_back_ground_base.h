
#pragma once

#include <memory>
#include <string>

#include "dxlib_resource_loader.h"
#include "i_entity.h"
#include "language_record.h"

namespace match_stick {

class LanguageBackGroundBase final : public IEntity {
public:
    LanguageBackGroundBase(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~LanguageBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override {
        ++counter_;

        return true;
    }

    void draw() const override;

private:
    const std::string title_text_;

    const int font_handle_;

    const int icon_handle_;

    int counter_{ 0 };
};

}  // namespace match_stick
