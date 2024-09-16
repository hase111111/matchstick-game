
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
    const int bgm_bar_x = GameConst::kResolutionX * 19 / 48;
    const int bgm_bar_y = GameConst::kResolutionY * 45 / 108;

    const int button_width2 = GameConst::kResolutionX / 24;

    const auto sound_change_bar_ptr = std::make_shared<SoundChangeBar>(
        language_record_ptr_, dxlib_input_ptr_, dxlib_resource_loader_ptr_, bgm_bar_x, bgm_bar_y);

    entity_updater_ptr->registerEntity(sound_change_bar_ptr);
    dxlib_user_interface_base_ptr->registerInterface(sound_change_bar_ptr, 5);

    // BGM 音量調整ボタン
    const auto bgm_volume_up5_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x - GameConst::kResolutionX * 57 / 192, bgm_bar_y - GameConst::kResolutionY * 3 / 108,
        button_width2, button_width2,
        "setting_volume_up", "data/font/azuki_font32.dft", [this]() { changeBGMVolume(5); });

    const auto bgm_volume_up_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x - GameConst::kResolutionX * 47 / 192, bgm_bar_y - GameConst::kResolutionY * 3 / 108,
        button_width2, button_width2,
        "setting_volume_up", "data/font/azuki_font32.dft", [this]() { changeBGMVolume(1); });

    const auto bgm_volume_down_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x + GameConst::kResolutionX * 47 / 192, bgm_bar_y - GameConst::kResolutionY * 3 / 108,
        button_width2, button_width2,
        "setting_volume_down", "data/font/azuki_font32.dft", [this]() { changeBGMVolume(-1); });

    const auto bgm_volume_down5_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x + GameConst::kResolutionX * 57 / 192, bgm_bar_y - GameConst::kResolutionY * 3 / 108,
        button_width2, button_width2,
        "setting_volume_down", "data/font/azuki_font32.dft", [this]() { changeBGMVolume(-5); });

    const auto sound_effect_volume_up5_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x - GameConst::kResolutionX * 57 / 192, bgm_bar_y + GameConst::kResolutionY * 15 / 108,
        button_width2, button_width2,
        "setting_volume_up", "data/font/azuki_font32.dft", [this]() { changeSEVolume(5); });

    const auto sound_effect_volume_up_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x - GameConst::kResolutionX * 47 / 192, bgm_bar_y + GameConst::kResolutionY * 15 / 108,
        button_width2, button_width2,
        "setting_volume_up", "data/font/azuki_font32.dft", [this]() { changeSEVolume(1); });


    const auto sound_effect_volume_down_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x + GameConst::kResolutionX * 47 / 192, bgm_bar_y + GameConst::kResolutionY * 15 / 108,
        button_width2, button_width2,
        "setting_volume_down", "data/font/azuki_font32.dft", [this]() { changeSEVolume(-1); });


    const auto sound_effect_volume_down5_button_ptr = std::make_shared<SimpleBoxButton>(
        language_record_ptr_, dxlib_resource_loader_ptr_,
        bgm_bar_x + GameConst::kResolutionX * 57 / 192, bgm_bar_y + GameConst::kResolutionY * 15 / 108,
        button_width2, button_width2,
        "setting_volume_down", "data/font/azuki_font32.dft", [this]() { changeSEVolume(-5); });

    entity_updater_ptr->registerEntity(bgm_volume_up5_button_ptr);
    entity_updater_ptr->registerEntity(bgm_volume_up_button_ptr);
    entity_updater_ptr->registerEntity(bgm_volume_down_button_ptr);
    entity_updater_ptr->registerEntity(bgm_volume_down5_button_ptr);
    entity_updater_ptr->registerEntity(sound_effect_volume_up5_button_ptr);
    entity_updater_ptr->registerEntity(sound_effect_volume_up_button_ptr);
    entity_updater_ptr->registerEntity(sound_effect_volume_down_button_ptr);
    entity_updater_ptr->registerEntity(sound_effect_volume_down5_button_ptr);

    dxlib_user_interface_base_ptr->registerInterface(bgm_volume_up5_button_ptr, 6);
    dxlib_user_interface_base_ptr->registerInterface(bgm_volume_up_button_ptr, 7);
    dxlib_user_interface_base_ptr->registerInterface(bgm_volume_down_button_ptr, 8);
    dxlib_user_interface_base_ptr->registerInterface(bgm_volume_down5_button_ptr, 9);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_up5_button_ptr, 10);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_up_button_ptr, 11);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_down_button_ptr, 12);
    dxlib_user_interface_base_ptr->registerInterface(sound_effect_volume_down5_button_ptr, 13);

    // 配置を設定
    dxlib_user_interface_base_ptr->registerInterfaceDeployment(0, 1, 3, 0, 0);
    dxlib_user_interface_base_ptr->registerInterfaceDeployment(1, 2, 0, 0, 1);
    dxlib_user_interface_base_ptr->registerInterfaceDeployment(2, 3, 1, 0, 2);
    dxlib_user_interface_base_ptr->registerInterfaceDeployment(3, 0, 2, 0, 2);

    dxlib_user_interface_base_ptr->setDefaultSelectedId(0);
}

void SettingSceneUiCreator::changeBGMVolume(const int volume_dif) {
    auto current_volume = dxlib_resource_loader_ptr_->getBGMVolumePercent();

    current_volume += volume_dif;

    if (current_volume < 0) {
        current_volume = 0;
    } else if (current_volume > 100) {
        current_volume = 100;
    }

    dxlib_resource_loader_ptr_->changeAllBGMVolume(current_volume);
}

void SettingSceneUiCreator::changeSEVolume(const int volume_dif) {
    auto current_volume = dxlib_resource_loader_ptr_->getSEVolumePercent();

    current_volume += volume_dif;

    if (current_volume < 0) {
        current_volume = 0;
    } else if (current_volume > 100) {
        current_volume = 100;
    }

    dxlib_resource_loader_ptr_->changeAllSEVolume(current_volume);
}

}  // namespace match_stick
