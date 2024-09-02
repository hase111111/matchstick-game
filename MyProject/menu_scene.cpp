
#include "menu_scene.h"

#include <format>

#include <magic_enum.hpp>
#include <DxLib.h>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "dxlib_user_interface_base.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "game_const.h"
#include "input_scheme_displayer.h"
#include "menu_back_ground_base.h"
#include "menu_button.h"
#include "simple_box_button.h"


namespace match_stick {

MenuScene::MenuScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                     const std::shared_ptr<const FpsController>& fps_controller_ptr,
                     const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                     const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                     const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);

    // ルール画面のエンティティを登録
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<MenuBackGroundBase>());

    // UI を構築
    const auto dxlib_user_interface_base_ptr = std::make_shared<DxLibUserInterfaceBase>(dxlib_input_ptr);
    entity_updater_ptr_->registerEntity(dxlib_user_interface_base_ptr);

    constexpr int ui_start_x = GameConst::kResolutionX * 73 / 1000;
    constexpr int ui_start_y = GameConst::kResolutionY / 27;
    constexpr int ui_interval = GameConst::kResolutionX / 48;
    constexpr int ui_width = GameConst::kResolutionX * 100 / 369;
    constexpr int ui_height = GameConst::kResolutionY * 100 / 257;

    const auto to_game_button_ptr = std::make_shared<MenuButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        ui_start_x + (ui_width * 2 + ui_interval) / 2, ui_start_y + ui_height / 2,
        "data/img/icon_game.png", "menu_game",
        [this]() {
            // シーン遷移
            scene_change_listener_ptr_->requestAddScene(SceneName::kDebug, SceneChangeParameter{});
        },
        true);
    entity_updater_ptr_->registerEntity(to_game_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_game_button_ptr, 0);

    const auto to_rule_button_ptr = std::make_shared<MenuButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        ui_start_x + (ui_width + ui_interval) * 2 + ui_width / 2, ui_start_y + ui_height / 2,
        "data/img/icon_rule.png", "menu_rule",
        [this]() {
            // シーン遷移
            scene_change_listener_ptr_->requestAddScene(SceneName::kRule, SceneChangeParameter{});
        });
    entity_updater_ptr_->registerEntity(to_rule_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_rule_button_ptr, 1);

    const auto to_setting_button_ptr = std::make_shared<MenuButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        ui_start_x + ui_width / 2, ui_start_y + ui_height * 3 / 2 + ui_interval,
        "data/img/icon_setting.png", "menu_setting",
        [this]() {
            // シーン遷移
            scene_change_listener_ptr_->requestAddScene(SceneName::kSetting, SceneChangeParameter{});
        });
    entity_updater_ptr_->registerEntity(to_setting_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_setting_button_ptr, 2);

    const auto to_replay_button_ptr = std::make_shared<MenuButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        ui_start_x + (ui_width + ui_interval) + ui_width / 2, ui_start_y + ui_height * 3 / 2 + ui_interval,
        "data/img/icon_replay.png", "menu_replay",
        [this]() {
            // ゲーム終了
            game_end_ = true;
        });
    entity_updater_ptr_->registerEntity(to_replay_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_replay_button_ptr, 3);

    const auto to_language_button_ptr = std::make_shared<MenuButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        ui_start_x + (ui_width + ui_interval) * 2 + ui_width / 2, ui_start_y + ui_height * 3 / 2 + ui_interval,
        "data/img/icon_language.png", "menu_language",
        [this]() {
            // シーン遷移
            scene_change_listener_ptr_->requestAddScene(SceneName::kLanguage, SceneChangeParameter{});
        });
    entity_updater_ptr_->registerEntity(to_language_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_language_button_ptr, 4);

    constexpr int button_width = GameConst::kResolutionX * 5 / 24;
    constexpr int button_height = GameConst::kResolutionY / 9;
    constexpr int button_diff = GameConst::kResolutionX / 96;

    const auto back_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        GameConst::kResolutionX - button_width / 2 - button_diff,
        GameConst::kResolutionY - button_height / 2 - button_diff,
        button_width, button_height, "menu_back", "data/font/azuki_font24.dft",
        [this]() {
            sceneBackCallback();
        });
    entity_updater_ptr_->registerEntity(back_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(back_button_ptr, 5);

    const auto game_end_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        GameConst::kResolutionX - button_width * 3 / 2 - button_diff * 2,
        GameConst::kResolutionY - button_height / 2 - button_diff,
        button_width, button_height, "menu_end", "data/font/azuki_font24.dft",
        [this]() {
            game_end_ = true;
        });
    entity_updater_ptr_->registerEntity(game_end_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(game_end_button_ptr, 6);

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool MenuScene::update() {
    entity_updater_ptr_->update();

    // ゲーム終了フラグが立っていたら，ゲームを終了する．
    if (game_end_) {
        return false;
    }

    return true;
}

void MenuScene::draw() const {
    entity_updater_ptr_->draw();
}

void MenuScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, MenuScene is returned from other scene.");

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);

    // フラグをリセット
    now_scene_change_ = false;
}

void MenuScene::sceneBackCallback() {
    if (now_scene_change_) {
        return;
    }

    DEBUG_PRINT("Return the scene to the previous one.");

    now_scene_change_ = true;

    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
        scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

void MenuScene::sceneChangeCallback(const SceneName scene_name) {
    if (now_scene_change_) {
        return;
    }

    DEBUG_PRINT(std::format("Change the scene to {}.", magic_enum::enum_name(scene_name)));

    now_scene_change_ = true;

    // フェードアウト演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this, scene_name]() {
        scene_change_listener_ptr_->requestAddScene(scene_name, SceneChangeParameter{});
    });

    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

}  // namespace match_stick

