
#include "scene_creator.h"

#include "debug_scene.h"
#include "dxlib_assert.h"
#include "game_scene.h"
#include "rule_scene.h"
#include "title_scene.h"

namespace match_stick {

SceneCreator::SceneCreator(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibKeyboard>& keyboard_ptr,
                           const std::shared_ptr<const DxLibMouse>& mouse_ptr,
                           const std::shared_ptr<BgmPlayer>& bgm_player_ptr,
                           const std::shared_ptr<FontLoader>& font_loader_ptr,
                           const std::shared_ptr<ImageLoader>& image_loader_ptr,
                           const std::shared_ptr<SoundEffectLoader>& sound_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    fps_controller_ptr_(fps_controller_ptr),
    language_record_ptr_(language_record_ptr),
    keyboard_ptr_(keyboard_ptr),
    mouse_ptr_(mouse_ptr),
    bgm_player_ptr_(bgm_player_ptr),
    font_loader_ptr_(font_loader_ptr),
    image_loader_ptr_(image_loader_ptr),
    sound_effect_loader_ptr_(sound_loader_ptr) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

    ASSERT_NOT_NULL_PTR(fps_controller_ptr_);

    ASSERT_NOT_NULL_PTR(keyboard_ptr_);
    ASSERT_NOT_NULL_PTR(mouse_ptr_);

    ASSERT_NOT_NULL_PTR(bgm_player_ptr_);
    ASSERT_NOT_NULL_PTR(font_loader_ptr_);
    ASSERT_NOT_NULL_PTR(image_loader_ptr_);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr_);
}

std::unique_ptr<IScene> SceneCreator::createScene(const SceneName scene_name) const {
    switch (scene_name) {
    case SceneName::kDebug: {
        return std::make_unique<DebugScene>(scene_change_listener_ptr_, keyboard_ptr_);
    }
    case SceneName::kGame: {
        return std::make_unique<GameScene>(
            scene_change_listener_ptr_,
            language_record_ptr_,
            keyboard_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kRule: {
        return std::make_unique<RuleScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            keyboard_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kTitle: {
        return std::make_unique<TitleScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            keyboard_ptr_,
            mouse_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    default: {
        ASSERT_MUST_NOT_REACH_HERE();
        return nullptr;
    }
    }  // switch
}

}  // namespace match_stick
