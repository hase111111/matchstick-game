﻿
#include "scene_creator.h"

#include "debug_scene.h"
#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "game_scene.h"
#include "language_scene.h"
#include "language_scene_resource_loader.h"
#include "menu_scene.h"
#include "menu_scene_resource_loader.h"
#include "rule_scene.h"
#include "rule_scene_resource_loader.h"
#include "setting_scene.h"
#include "title_scene.h"
#include "title_scene_resource_loader.h"

namespace match_stick {

SceneCreator::SceneCreator(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibInput>& input_ptr,
                           const std::shared_ptr<BgmPlayer>& bgm_player_ptr,
                           const std::shared_ptr<FontLoader>& font_loader_ptr,
                           const std::shared_ptr<ImageLoader>& image_loader_ptr,
                           const std::shared_ptr<SoundEffectLoader>& sound_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    fps_controller_ptr_(fps_controller_ptr),
    language_record_ptr_(language_record_ptr),
    input_ptr_(input_ptr),
    bgm_player_ptr_(bgm_player_ptr),
    font_loader_ptr_(font_loader_ptr),
    image_loader_ptr_(image_loader_ptr),
    sound_effect_loader_ptr_(sound_loader_ptr) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(input_ptr);
    ASSERT_NOT_NULL_PTR(bgm_player_ptr);
    ASSERT_NOT_NULL_PTR(font_loader_ptr);
    ASSERT_NOT_NULL_PTR(image_loader_ptr);
    ASSERT_NOT_NULL_PTR(sound_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr_);
    ASSERT_NOT_NULL_PTR(language_record_ptr_);
    ASSERT_NOT_NULL_PTR(input_ptr_);
    ASSERT_NOT_NULL_PTR(bgm_player_ptr_);
    ASSERT_NOT_NULL_PTR(font_loader_ptr_);
    ASSERT_NOT_NULL_PTR(image_loader_ptr_);
    ASSERT_NOT_NULL_PTR(sound_effect_loader_ptr_);
}

std::unique_ptr<IScene> SceneCreator::createScene(const SceneName scene_name) const {
    switch (scene_name) {
    case SceneName::kDebug: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kDebug");
        return std::make_unique<DebugScene>(scene_change_listener_ptr_, input_ptr_);
    }
    case SceneName::kGame: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kGame");
        return std::make_unique<GameScene>(
            scene_change_listener_ptr_,
            language_record_ptr_,
            input_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kLanguage: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kLanguage");

        // 言語シーンのリソースをロード
        LanguageSceneResourceLoader language_scene_resource_loader(
            font_loader_ptr_, image_loader_ptr_, sound_effect_loader_ptr_);

        language_scene_resource_loader.loadImage();

        return std::make_unique<LanguageScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            input_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kMenu: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kMenu");

        // メニューシーンのリソースをロード
        MenuSceneResourceLoader menu_scene_resource_loader(
            font_loader_ptr_, image_loader_ptr_, sound_effect_loader_ptr_);

        menu_scene_resource_loader.loadImage();

        return std::make_unique<MenuScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            input_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kRule: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kRule");

        // ルールシーンのリソースをロード
        RuleSceneResourceLoader rule_scene_resource_loader(
            font_loader_ptr_, image_loader_ptr_, sound_effect_loader_ptr_);

        rule_scene_resource_loader.loadImage();

        return std::make_unique<RuleScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            input_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kTitle: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kTitle");

        // タイトルシーンのリソースをロード
        TitleSceneResourceLoader title_scene_resource_loader(
            font_loader_ptr_, image_loader_ptr_, sound_effect_loader_ptr_);

        title_scene_resource_loader.loadImage();

        return std::make_unique<TitleScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            input_ptr_,
            font_loader_ptr_,
            image_loader_ptr_,
            sound_effect_loader_ptr_);
    }
    case SceneName::kSetting: {
        DEBUG_PRINT_IMPORTANT("SceneCreator::createScene() SceneName::kSetting");

        return std::make_unique<SettingScene>(
            scene_change_listener_ptr_,
            fps_controller_ptr_,
            language_record_ptr_,
            input_ptr_,
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
