
#pragma once

#include <memory>
#include <string>

#include "dxlib_resource_loader.h"
#include "i_entity.h"
#include "language_record.h"

namespace match_stick {

class SettingBackGroundBase final : public IEntity {
public:
    SettingBackGroundBase(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                          const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~SettingBackGroundBase() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override;

    void draw() const override;

private:
    const std::string title_text_;

    const int font48_handle_;

    const int icon_handle_;

    int counter_{ 0 };
};

}  // namespace match_stick
