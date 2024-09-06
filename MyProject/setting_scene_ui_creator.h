
#pragma once

#include <memory>

#include "dxlib_input.h"
#include "dxlib_resource_loader.h"
#include "entity_updater.h"
#include "language_record.h"
#include "scene_change_listener.h"

namespace match_stick {

class SettingSceneUiCreator final {
public:
    SettingSceneUiCreator(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                          const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                          const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                          const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr);
    ~SettingSceneUiCreator() = default;

    void initUI(const std::unique_ptr<EntityUpdater>& entity_updater_ptr_);

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;
    const std::shared_ptr<const LanguageRecord> language_record_ptr_;
    const std::shared_ptr<const DxLibInput> dxlib_input_ptr_;
    const std::shared_ptr<DxLibResourceLoader> dxlib_resource_loader_ptr_;
};

}  // namespace match_stick
