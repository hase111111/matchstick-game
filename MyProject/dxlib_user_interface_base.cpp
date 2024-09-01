
#include "dxlib_user_interface_base.h"

#include <format>

#include <DxLib.h>

#include "dxlib_assert.h"

namespace match_stick {

DxLibUserInterfaceBase::DxLibUserInterfaceBase(const std::shared_ptr<const DxLibInput>& dxlib_input) :
    dxlib_input_(dxlib_input) {
    // nullptr でないことを確認
    ASSERT_NOT_NULL_PTR(dxlib_input_);
}

void DxLibUserInterfaceBase::registerInterface(
    const std::shared_ptr<IDxLibUserInterface>& dxlib_interface, const int id) {
    // すでに登録されている場合はアサートを出す
    ASSERT(dxlib_interfaces_.find(id) == dxlib_interfaces_.end(), std::format("id ({}) duplicated", id));

    // id が負の場合はアサートを出す
    ASSERT(id >= 0, std::format("id ({}) is negative", id));

    // 登録する
    dxlib_interfaces_[id] = dxlib_interface;

    // 選択中のボタンに登録されたボタンを設定する
    selected_id_ = id;
}

void DxLibUserInterfaceBase::registerInterfaceDeployment(const std::map<int, DxLibInterfaceDeployment>& map) {
    // 登録する
    deployment_map_ = map;

    // マップが正しいか確認する
    ASSERT(validateDeploymentMap(), "Deployment map is invalid.");
}

void DxLibUserInterfaceBase::setDefaultSelectedId(const int id) {
    // id が負の場合はアサートを出す
    ASSERT(id >= 0, std::format("id ({}) is negative", id));

    // 登録する
    default_selected_id_ = id;
    selected_id_ = id;
}

bool DxLibUserInterfaceBase::update() {
    using enum DxLibInput::InputType;

    // ボタンが登録されていない場合は何もしない
    if (dxlib_interfaces_.empty()) {
        return true;
    }

    // 選択中のボタンを保存
    const int now_selected_id = selected_id_;

    // 選択中のボタンを更新
    if (dxlib_input_->getInputType() == kKeyboard) {
        updateSelectedIdWhenMouseUsed();
    } else if (dxlib_input_->getInputType() == kMouse) {
        updateSelectedIdWhenKeyboardUsed();
    } else {
        ASSERT_MUST_NOT_REACH_HERE();
    }

    // 選択中のボタンが変わった場合，ホバーのコールバックを呼ぶ
    if (now_selected_id != selected_id_) {
        if (now_selected_id != kNoSelectedId) {
            dxlib_interfaces_[now_selected_id]->callbackWhenHoverEnded();
        }
        if (selected_id_ != kNoSelectedId) {
            dxlib_interfaces_[selected_id_]->callbackWhenHoverStarted();
        }
    }

    // 決定ボタンが押されたら，選択中のボタンを押す
    if (dxlib_input_->getKeyboardPressingCount(KEY_INPUT_Z) == 1 ||
        dxlib_input_->getMousePressingCount(MOUSE_INPUT_LEFT) == 1) {
        if (selected_id_ != kNoSelectedId) {
            dxlib_interfaces_[selected_id_]->callbackWhenClicked();
        }
    }

    return true;
}

bool DxLibUserInterfaceBase::validateDeploymentMap() const {
    // map に存在しているインターフェイスの id が実際に登録されているか確認する
    for (const auto& [id, deployment] : deployment_map_) {
        if (!dxlib_interfaces_.contains(id)) {
            return false;
        }

        for (const auto& [direction, interface_id] : deployment.deployment_map) {
            if (!dxlib_interfaces_.contains(interface_id)) {
                return false;
            }
        }
    }

    return true;
}

void DxLibUserInterfaceBase::updateSelectedIdWhenMouseUsed() {
    // 選択中のボタンを更新
    for (const auto& [id, dxlib_interface] : dxlib_interfaces_) {
        if (dxlib_interface->isHovered(dxlib_input_->getCursorPosX(), dxlib_input_->getCursorPosY())) {
            selected_id_ = id;
            return;
        }
    }

    selected_id_ = kNoSelectedId;
}

void DxLibUserInterfaceBase::updateSelectedIdWhenKeyboardUsed() {
    // キーボード操作を行う場合は，選択されていない状態を許可しない．
    selected_id_ = selected_id_ == kNoSelectedId ? 0 : selected_id_;
}

}  // namespace match_stick
