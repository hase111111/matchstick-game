
#include "setting_scene.h"

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "dxlib_user_interface_base.h"
#include "fade_effect.h"
#include "fps_displayer.h"
#include "game_const.h"
#include "input_scheme_displayer.h"
#include "setting_back_ground_base.h"
#include "simple_box_button.h"

namespace match_stick {

SettingScene::SettingScene(const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
                           const std::shared_ptr<const FpsController>& fps_controller_ptr,
                           const std::shared_ptr<const LanguageRecord>& language_record_ptr,
                           const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
                           const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    entity_updater_ptr_(std::make_unique<EntityUpdater>()) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(fps_controller_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(entity_updater_ptr_);

    // エンティティを追加
    entity_updater_ptr_->registerEntity(std::make_unique<SettingBackGroundBase>(
        language_record_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<FpsDisplayer>(
        fps_controller_ptr, language_record_ptr, dxlib_resource_loader_ptr));
    entity_updater_ptr_->registerEntity(std::make_shared<InputSchemeDisplayer>(
        dxlib_input_ptr, dxlib_resource_loader_ptr));

    initUI(language_record_ptr, dxlib_input_ptr, dxlib_resource_loader_ptr);

    // フェードイン演出を追加
    const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeIn, []() {});
    entity_updater_ptr_->registerEntity(fade_effect_ptr);
}

bool SettingScene::update() {
    entity_updater_ptr_->update();

    return true;
}

void SettingScene::draw() const {
    entity_updater_ptr_->draw();
}

void SettingScene::onReturnFromOtherScene(const SceneChangeParameter&) {
    DEBUG_PRINT_IMPORTANT("Now, SettingScene is returned from other scene.");
}

void SettingScene::initUI(
    const std::shared_ptr<const LanguageRecord>& language_record_ptr,
    const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
    const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    // UI Base を追加
    const auto dxlib_user_interface_base_ptr = std::make_shared<DxLibUserInterfaceBase>(dxlib_input_ptr);
    entity_updater_ptr_->registerEntity(dxlib_user_interface_base_ptr);

    constexpr int button_center_x = GameConst::kResolutionX * 7 / 8;

    constexpr int button_y_diff = GameConst::kResolutionY / 32;

    constexpr int button_width = GameConst::kResolutionX * 5 / 24;
    constexpr int button_height = GameConst::kResolutionY / 9;

    // 戻るボタン
    const auto button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        button_center_x, GameConst::kResolutionY - button_y_diff - button_height / 2,
        button_width, button_height,
        "setting_back", "data/font/azuki_font24.dft",
        [this]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
            });

            entity_updater_ptr_->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr_->registerEntity(button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(button_ptr, 0);

    // 適用して戻るボタン
    const auto apply_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        button_center_x, GameConst::kResolutionY - button_y_diff * 2 - button_height * 3 / 2,
        button_width, button_height,
        "setting_apply_and_back", "data/font/azuki_font24.dft",
        [this]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteAllScene();
            });

            entity_updater_ptr_->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr_->registerEntity(apply_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(apply_button_ptr, 1);

    // リセットボタン
    const auto reset_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        button_center_x, GameConst::kResolutionY - button_y_diff * 3 - button_height * 5 / 2,
        button_width, button_height,
        "setting_reset", "data/font/azuki_font24.dft",
        [this]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteAllScene();
            });

            entity_updater_ptr_->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr_->registerEntity(reset_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(reset_button_ptr, 2);

    // クレジットへ
    const auto to_credit_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        button_center_x, GameConst::kResolutionY - button_y_diff * 4 - button_height * 7 / 2,
        button_width, button_height,
        "setting_to_credit", "data/font/azuki_font24.dft",
        [this]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestAddScene(SceneName::kDebug, SceneChangeParameter{});
            });

            entity_updater_ptr_->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr_->registerEntity(to_credit_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_credit_button_ptr, 3);

    // 操作方法へ
    const auto to_how_to_play_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr, dxlib_resource_loader_ptr,
        button_center_x, GameConst::kResolutionY - button_y_diff * 5 - button_height * 9 / 2,
        button_width, button_height,
        "setting_to_control", "data/font/azuki_font24.dft",
        [this]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestAddScene(SceneName::kDebug, SceneChangeParameter{});
            });

            entity_updater_ptr_->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr_->registerEntity(to_how_to_play_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_how_to_play_button_ptr, 4);
}

}  // namespace match_stick
