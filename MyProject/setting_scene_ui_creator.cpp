
#include "setting_scene_ui_creator.h"

#include <memory>

#include "dxlib_assert.h"
#include "dxlib_user_interface_base.h"
#include "game_const.h"
#include "fade_effect.h"
#include "simple_box_button.h"
#include "sound_change_bar.h"

namespace match_stick {

SettingSceneUiCreator::SettingSceneUiCreator(
    const std::shared_ptr<SceneChangeListener>& scene_change_listener_ptr,
    const std::shared_ptr<const LanguageRecord>& language_record_ptr,
    const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
    const std::shared_ptr<DxLibResourceLoader>& dxlib_resource_loader_ptr) :
    scene_change_listener_ptr_(scene_change_listener_ptr),
    language_record_ptr_(language_record_ptr),
    dxlib_input_ptr_(dxlib_input_ptr),
    dxlib_resource_loader_ptr_(dxlib_resource_loader_ptr) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr);
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(scene_change_listener_ptr_);
    ASSERT_NOT_NULL_PTR(language_record_ptr_);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr_);
}

void SettingSceneUiCreator::initUI(const std::unique_ptr<EntityUpdater>& entity_updater_ptr) {
    // ヌルチェック
    ASSERT_NOT_NULL_PTR(entity_updater_ptr);

    // UI Base を追加
    const auto dxlib_user_interface_base_ptr = std::make_shared<DxLibUserInterfaceBase>(dxlib_input_ptr_);
    entity_updater_ptr->registerEntity(dxlib_user_interface_base_ptr);

    constexpr int button_center_x = GameConst::kResolutionX * 7 / 8;

    constexpr int button_y_diff = GameConst::kResolutionY / 32;

    constexpr int button_width = GameConst::kResolutionX * 5 / 24;
    constexpr int button_height = GameConst::kResolutionY / 9;

    // 戻るボタン
    const auto button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        button_center_x, GameConst::kResolutionY - button_y_diff - button_height / 2,
        button_width, button_height,
        "setting_back", "data/font/azuki_font24.dft",
        [this, &entity_updater_ptr]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteScene(1, SceneChangeParameter{});
            });

            entity_updater_ptr->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr->registerEntity(button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(button_ptr, 0);

    // 適用して戻るボタン
    const auto apply_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        button_center_x, GameConst::kResolutionY - button_y_diff * 2 - button_height * 3 / 2,
        button_width, button_height,
        "setting_apply_and_back", "data/font/azuki_font24.dft",
        [this, &entity_updater_ptr]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteAllScene();
            });

            entity_updater_ptr->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr->registerEntity(apply_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(apply_button_ptr, 1);

    // リセットボタン
    const auto reset_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        button_center_x, GameConst::kResolutionY - button_y_diff * 3 - button_height * 5 / 2,
        button_width, button_height,
        "setting_reset", "data/font/azuki_font24.dft",
        [this, &entity_updater_ptr]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestDeleteAllScene();
            });

            entity_updater_ptr->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr->registerEntity(reset_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(reset_button_ptr, 2);

    // クレジットへ
    const auto to_credit_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        button_center_x, GameConst::kResolutionY - button_y_diff * 4 - button_height * 7 / 2,
        button_width, button_height,
        "setting_to_credit", "data/font/azuki_font24.dft",
        [this, &entity_updater_ptr]() {
            // フェードアウト演出を追加
            const auto fade_effect_ptr = std::make_shared<FadeEffect>(30, FadeEffect::FadeType::kFadeOut, [this]() {
                scene_change_listener_ptr_->requestAddScene(SceneName::kDebug, SceneChangeParameter{});
            });

            entity_updater_ptr->registerEntity(fade_effect_ptr);
        });
    entity_updater_ptr->registerEntity(to_credit_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(to_credit_button_ptr, 3);

    // 音量調整バー
    const auto sound_change_bar_ptr = std::make_shared<SoundChangeBar>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        GameConst::kResolutionX / 2 - 100, GameConst::kResolutionY / 2);

    entity_updater_ptr->registerEntity(sound_change_bar_ptr);
    dxlib_user_interface_base_ptr->registerInterface(sound_change_bar_ptr, 5);

    const auto sound_effect_volume_up_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        GameConst::kResolutionX / 2 + 100, GameConst::kResolutionY / 2 - 50,
        50, 50,
        "setting_volume_up", "data/font/azuki_font32.dft",
        [this]() {
            auto volume = dxlib_resource_loader_ptr_->getVolumePercent();
            volume = volume + 10 > 100 ? 100 : volume + 10;
            dxlib_resource_loader_ptr_->changeAllSoundVolume(volume);
        });
    entity_updater_ptr->registerEntity(sound_effect_volume_up_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_up_button_ptr, 6);

    const auto sound_effect_volume_down_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        GameConst::kResolutionX / 2 + 100, GameConst::kResolutionY / 2 + 50,
        50, 50,
        "setting_volume_down", "data/font/azuki_font32.dft",
        [this]() {
            auto volume = dxlib_resource_loader_ptr_->getVolumePercent();
            volume = volume - 10 < 0 ? 0 : volume - 10;
            dxlib_resource_loader_ptr_->changeAllSoundVolume(volume);
        });
    entity_updater_ptr->registerEntity(sound_effect_volume_down_button_ptr);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_down_button_ptr, 7);
}

}  // namespace match_stick
