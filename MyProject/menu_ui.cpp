
#include "menu_ui.h"

#include <format>

#include <DxLib.h>
#include <magic_enum.hpp>

#include "dxlib_assert.h"
#include "dxlib_debug_print.h"
#include "game_const.h"
#include "math_const.h"

namespace {

static constexpr int kBarWidth = 260;
static constexpr int kBarHeight = 210;
static constexpr int kBarThickness = 3;

static constexpr int kBarStartX = 70;
static constexpr int kBarStartY = 20;
static constexpr int kBarDistance = 20;

static constexpr int kButtonWidth = 200;
static constexpr int kButtonHeight = 60;
static constexpr int kButtonRight = 10;
static constexpr int kButtonBottom = 10;

static constexpr int kIndexMaxX = 3;
static constexpr int kIndexMaxY = 3;

}  // namespace

namespace match_stick {

MenuUI::MenuUI(const std::shared_ptr<const LanguageRecord>& language_record_ptr,
               const std::shared_ptr<const DxLibInput>& dxlib_input_ptr,
               const std::shared_ptr<const DxLibResourceLoader>& dxlib_resource_loader_ptr,
               const std::function<void()>& game_end_callback,
               const std::function<void()>& scene_back_callback,
               const std::function<void(SceneName)>& scene_change_callback) :
    dxlib_input_ptr_(dxlib_input_ptr),
    font48_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font48.dft")),
    font32_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font32.dft")),
    font24_handle_(dxlib_resource_loader_ptr->getFontHandle(language_record_ptr->getCurrentCountry(),
        "data/font/azuki_font24.dft")),
    select_sound_effect_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/selecting3.mp3")),
    decision_sound_effect_handle_(dxlib_resource_loader_ptr->getSoundHandle("data/sound/selecting2.mp3")),
    button0_text_(language_record_ptr->getValue("menu_back")),
    button1_text_(language_record_ptr->getValue("menu_end")),
    game_end_callback_(game_end_callback),
    scene_back_callback_(scene_back_callback),
    scene_change_callback_(scene_change_callback) {
    // ポインタが nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(language_record_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_input_ptr);
    ASSERT_NOT_NULL_PTR(dxlib_resource_loader_ptr);

    ASSERT_NOT_NULL_PTR(dxlib_input_ptr_);

    // 画像を読み込む
    bar_image_handle_map_[BarType::kGameStart] = dxlib_resource_loader_ptr->getImageHandle("data/img/icon_game.png");
    bar_image_handle_map_[BarType::kRule] = dxlib_resource_loader_ptr->getImageHandle("data/img/icon_rule.png");
    bar_image_handle_map_[BarType::kSetting] = dxlib_resource_loader_ptr->getImageHandle("data/img/icon_setting.png");
    bar_image_handle_map_[BarType::kReplay] = dxlib_resource_loader_ptr->getImageHandle("data/img/icon_replay.png");
    bar_image_handle_map_[BarType::kLanguage] = dxlib_resource_loader_ptr->getImageHandle("data/img/icon_language.png");

    // 回転を初期化
    for (const auto bar_type : magic_enum::enum_values<BarType>()) {
        bar_rotation_map_[bar_type] = 0.0;
    }

    // テキストを初期化
    bar_text_map_[BarType::kGameStart] = language_record_ptr->getValue("menu_game");
    bar_text_map_[BarType::kRule] = language_record_ptr->getValue("menu_rule");
    bar_text_map_[BarType::kSetting] = language_record_ptr->getValue("menu_setting");
    bar_text_map_[BarType::kReplay] = language_record_ptr->getValue("menu_replay");
    bar_text_map_[BarType::kLanguage] = language_record_ptr->getValue("menu_language");
}

bool MenuUI::update() {
    // 回転を更新
    updateRotation();

    // 選択を更新
    updateSelectedBarType();

    if (selected_bar_type_ != getBarTypeFromIndex()) {
        selected_bar_type_ = getBarTypeFromIndex();
        bar_rotation_map_[selected_bar_type_] = MathConst<double>::kPi * 2.0;

        PlaySoundMem(select_sound_effect_handle_, DX_PLAYTYPE_BACK);

        DEBUG_PRINT(std::format("index_x:={}, index_y:={}",
            selected_bar_index_x_ % kIndexMaxX, selected_bar_index_y_ % kIndexMaxY));
    }

    if (dxlib_input_ptr_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1 ||
        dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_Z) == 1) {
        const int index_x = selected_bar_index_x_ % kIndexMaxX;
        const int index_y = selected_bar_index_y_ % kIndexMaxY;

        if (index_y == 0 && (index_x == 0 || index_x == 1)) {
            scene_change_callback_(SceneName::kGame);
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_x == 2 && index_y == 0) {
            scene_change_callback_(SceneName::kRule);
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_x == 0 && index_y == 1) {
            scene_change_callback_(SceneName::kSetting);
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_x == 1 && index_y == 1) {
            scene_change_callback_(SceneName::kDebug);
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_x == 2 && index_y == 1) {
            scene_change_callback_(SceneName::kLanguage);
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_y == 2 && (index_x == 0 || index_x == 1)) {
            scene_back_callback_();
            PlaySoundMem(decision_sound_effect_handle_, DX_PLAYTYPE_BACK);
        } else if (index_y == 2 && index_x == 2) {
            game_end_callback_();
        }
    }

    ++counter_;

    return true;
}

void MenuUI::draw() const {
    drawBar();

    drawButton();
}

void MenuUI::updateRotation() {
    for (auto& pair : bar_rotation_map_) {
        if (pair.second > 0.0) {
            pair.second -= 0.5;
        } else if (pair.second < 0.0) {
            pair.second = 0.0;
        }
    }
}

void MenuUI::updateSelectedBarType() {
    if (dxlib_input_ptr_->getInputType() == DxLibInput::InputType::kKeyboard) {
        // 横方向の選択
        if (selected_bar_index_y_ % kIndexMaxY == 0 || selected_bar_index_y_ % kIndexMaxY == 2) {
            if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1) {
                selected_bar_index_x_ = selected_bar_index_x_ % kIndexMaxX == 2 ? 0 : 2;
            } else if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
                selected_bar_index_x_ = selected_bar_index_x_ % kIndexMaxX == 2 ? 0 : 2;
            }
        } else {
            if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_LEFT) == 1) {
                selected_bar_index_x_ += kIndexMaxX - 1;
            } else if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_RIGHT) == 1) {
                selected_bar_index_x_ += 1;
            }
        }

        // 縦方向の選択
        if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_UP) == 1) {
            selected_bar_index_y_ += kIndexMaxY - 1;
        } else if (dxlib_input_ptr_->getKeyboardPressingCount(KEY_INPUT_DOWN) == 1) {
            selected_bar_index_y_ += 1;
        }
    } else {
        const int input_x = dxlib_input_ptr_->getCursorPosX();
        const int input_y = dxlib_input_ptr_->getCursorPosY();

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < kIndexMaxX; ++j) {
                if (i == 0 && j == 0) { continue; }
                if (i == 0 && j == 1) { continue; }

                const int x = kBarStartX + (kBarWidth + kBarDistance) * j;
                const int y = kBarStartY + (kBarHeight + kBarDistance) * i;

                if (x <= input_x && input_x <= x + kBarWidth &&
                    y <= input_y && input_y <= y + kBarHeight) {
                    selected_bar_index_x_ = j;
                    selected_bar_index_y_ = i;
                }
            }
        }

        if (kBarStartX <= input_x && input_x <= kBarStartX + kBarWidth * 2 + kBarDistance &&
                   kBarStartY <= input_y && input_y <= kBarStartY + kBarHeight) {
            selected_bar_index_x_ = 0;
            selected_bar_index_y_ = 0;
        }

        // 下のボタン
        if (GameConst::kResolutionX - kButtonWidth * 2 - kButtonRight <= input_x &&
            input_x <= GameConst::kResolutionX - kButtonRight &&
            GameConst::kResolutionY - kButtonBottom - kButtonHeight <= input_y &&
            input_y <= GameConst::kResolutionY - kButtonBottom) {
            selected_bar_index_x_ = 0;
            selected_bar_index_y_ = 2;
        }

        if (GameConst::kResolutionX - kButtonWidth - kButtonRight <= input_x &&
            input_x <= GameConst::kResolutionX - kButtonRight &&
            GameConst::kResolutionY - kButtonBottom - kButtonHeight <= input_y &&
            input_y <= GameConst::kResolutionY - kButtonBottom) {
            selected_bar_index_x_ = 2;
            selected_bar_index_y_ = 2;
        }
    }
}

MenuUI::BarType MenuUI::getBarTypeFromIndex() const {
    const int index_x = selected_bar_index_x_ % kIndexMaxX;
    const int index_y = selected_bar_index_y_ % kIndexMaxY;

    if ((index_x == 0 && index_y == 0) || (index_x == 1 && index_y == 0)) {
        return BarType::kGameStart;
    } else if (index_x == 2 && index_y == 0) {
        return BarType::kRule;
    } else if (index_x == 0 && index_y == 1) {
        return BarType::kSetting;
    } else if (index_x == 1 && index_y == 1) {
        return BarType::kReplay;
    } else if (index_x == 2 && index_y == 1) {
        return BarType::kLanguage;
    } else if ((index_x == 0 && index_y == 2) || (index_x == 1 && index_y == 2)) {
        return BarType::kButton0;
    } else if (index_x == 2 && index_y == 2) {
        return BarType::kButton1;
    }

    ASSERT_MUST_NOT_REACH_HERE();
    return BarType::kGameStart;
}

void MenuUI::drawBar() const {
    const unsigned int bar_color = GetColor(0x61, 0x61, 0x61);
    const unsigned int bar_inner_color = GetColor(0xe5, 0xe5, 0xe5);
    const unsigned int bar_hovered_color = GetColor(0xc0, 0xc0, 0xc0);

    // 縦2 × 横3のバーを描画
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            const BarType bar_type = static_cast<BarType>(j + i * 3 - 1);

            if (i == 0 && j == 0) { continue; }
            if (i == 0 && j == 1) { continue; }

            DrawBox(kBarStartX + (kBarWidth + kBarDistance) * j,
                    kBarStartY + (kBarHeight + kBarDistance) * i,
                    kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight,
                    bar_color, TRUE);

            DrawBox(kBarStartX + (kBarWidth + kBarDistance) * j + kBarThickness,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarThickness,
                    kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth - kBarThickness,
                    kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight - kBarThickness,
                    (bar_type == selected_bar_type_) ? bar_hovered_color : bar_inner_color, TRUE);

            // 画像を描画
            const int image_handle = bar_image_handle_map_.at(bar_type);
            DrawRotaGraph(kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth / 2,
                          kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight * 2 / 3,
                          0.8, bar_rotation_map_.at(bar_type), image_handle, TRUE);

            // テキストを描画
            const int text_width = GetDrawStringWidthToHandle(bar_text_map_.at(bar_type).c_str(),
                static_cast<int>(bar_text_map_.at(bar_type).size()), font32_handle_);
            DrawStringToHandle(kBarStartX + (kBarWidth + kBarDistance) * j + kBarWidth / 2 - text_width / 2,
                               kBarStartY + (kBarHeight + kBarDistance) * i + kBarHeight / 5 - 20,
                               bar_text_map_.at(bar_type).c_str(),
                               GetColor(0x00, 0x00, 0x00), font32_handle_);
        }
    }

    // 左上のバーは2つのバーを合わせたもの
    DrawBox(kBarStartX, kBarStartY, kBarStartX + kBarWidth * 2 + kBarDistance, kBarStartY + kBarHeight,
            bar_color, TRUE);

    DrawBox(kBarStartX + kBarThickness,
            kBarStartY + kBarThickness,
            kBarStartX + kBarWidth * 2 + kBarDistance - kBarThickness,
            kBarStartY + kBarHeight - kBarThickness,
            (BarType::kGameStart == selected_bar_type_) ? bar_hovered_color : bar_inner_color, TRUE);

    // 画像を描画
    const int image_handle = bar_image_handle_map_.at(BarType::kGameStart);
    DrawRotaGraph(kBarStartX + kBarWidth / 3 + kBarDistance / 2,
                  kBarStartY + kBarHeight / 2,
                  1.0, bar_rotation_map_.at(BarType::kGameStart), image_handle, TRUE);

    // テキストを描画
    const int text_width = GetDrawStringWidthToHandle(bar_text_map_.at(BarType::kGameStart).c_str(),
            static_cast<int>(bar_text_map_.at(BarType::kGameStart).size()), font48_handle_);
    DrawStringToHandle(kBarStartX + kBarWidth * 5 / 4 + kBarDistance / 2 - text_width / 2,
                       kBarStartY + kBarHeight / 3 - 20,
                       bar_text_map_.at(BarType::kGameStart).c_str(),
                       GetColor(0x00, 0x00, 0x00), font48_handle_);
}

void MenuUI::drawButton() const {
    const unsigned int bar_color = GetColor(0x61, 0x61, 0x61);
    const unsigned int bar_inner_color = GetColor(0xda, 0xda, 0xda);
    const unsigned int bar_hovered_color = GetColor(0xc0, 0xc0, 0xc0);

    const int index_x = selected_bar_index_x_ % kIndexMaxX;
    const int index_y = selected_bar_index_y_ % kIndexMaxY;

    // ボタンを描画
    for (int i = 0; i < 2; ++i) {
        DrawBox(GameConst::kResolutionX - kButtonWidth + i * (kButtonWidth + kBarThickness) - kButtonRight,
                GameConst::kResolutionY - kButtonBottom,
                GameConst::kResolutionX - kButtonWidth * 2 + i * (kButtonWidth + kBarThickness) - kButtonRight,
                GameConst::kResolutionY - kButtonBottom - kButtonHeight,
                bar_color, TRUE);

        unsigned int color = bar_inner_color;

        if (index_y == 2 && (index_x == 0 || index_x == 1) && i == 0) {
            color = bar_hovered_color;
        }

        if (index_y == 2 && index_x == 2 && i == 1) {
            color = bar_hovered_color;
        }

        const int button_width = kButtonWidth + kBarThickness;

        DrawBox(GameConst::kResolutionX - kButtonWidth + i * button_width - kButtonRight - kBarThickness,
                GameConst::kResolutionY - kButtonBottom - kBarThickness,
                GameConst::kResolutionX - kButtonWidth * 2 + i * button_width - kButtonRight + kBarThickness,
                GameConst::kResolutionY - kButtonBottom - kButtonHeight + kBarThickness,
                color, TRUE);

        // テキストを描画
        const std::string text = (i == 0) ? button0_text_ : button1_text_;
        const int text_width =
            GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(text.size()), font24_handle_);

        DrawStringToHandle(GameConst::kResolutionX - kButtonWidth * 2 + i * (kButtonWidth + kBarThickness)
                                - kButtonRight + kButtonWidth / 2 - text_width / 2,
                           GameConst::kResolutionY - kButtonBottom - kButtonHeight / 2 - 12,
                           text.c_str(), GetColor(0x00, 0x00, 0x00), font24_handle_);
    }
}

}  // namespace match_stick
