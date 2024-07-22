
#pragma once

#include <memory>

#include "bgm_player.h"
#include "dxlib_keyboard.h"
#include "dxlib_mouse.h"
#include "font_loader.h"
#include "i_scene.h"
#include "image_loader.h"
#include "language_record.h"
#include "scene_name.h"
#include "scene_change_listener.h"
#include "sound_effect_loader.h"

namespace match_stick {

class SceneCreator final
{
public:
    SceneCreator(
        const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
        const std::shared_ptr<const LanguageRecord>& language_record_ptr,
        const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr,
        const std::shared_ptr<const DxLibMouse>& mouse_ptr,
        const std::shared_ptr<BgmPlayer>& bgm_player_ptr,
        const std::shared_ptr<FontLoader>& font_loader_ptr,
        const std::shared_ptr<ImageLoader>& image_loader_ptr,
        const std::shared_ptr<SoundEffectLoader>& sound_effect_loader_ptr);
    ~SceneCreator() = default;

    std::unique_ptr<IScene> createScene(SceneName scene_name) const;

private:
    const std::shared_ptr<SceneChangeListener> scene_change_listener_ptr_;

    const std::shared_ptr<const LanguageRecord> language_record_ptr_;

    const std::shared_ptr<const DxLibKeyboard> keyboard_ptr_;
    const std::shared_ptr<const DxLibMouse> mouse_ptr_;

    const std::shared_ptr<BgmPlayer> bgm_player_ptr_;
    const std::shared_ptr<FontLoader> font_loader_ptr_;
    const std::shared_ptr<ImageLoader> image_loader_ptr_;
    const std::shared_ptr<SoundEffectLoader> sound_effect_loader_ptr_;
};

}  // namespace match_stick
