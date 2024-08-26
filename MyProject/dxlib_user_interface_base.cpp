
#include "dxlib_user_interface_base.h"

#include <format>

#include "dxlib_assert.h"

namespace match_stick {

void DxLibUserInterfaceBase::registerInterface(
    const std::shared_ptr<IDxLibInterface>& dxlib_interface, const int id) {
    // すでに登録されている場合はアサートを出す
    ASSERT(dxlib_interfaces_.find(id) == dxlib_interfaces_.end(), std::format("id ({}) duplicated", id));

    // id が負の場合はアサートを出す
    ASSERT(id >= 0, std::format("id ({}) is negative", id));

    // 登録する
    dxlib_interfaces_[id] = dxlib_interface;
}

void DxLibUserInterfaceBase::registerInterfaceDeployment(const std::map<int, std::vector<int>>& deployment_map) {}

bool DxLibUserInterfaceBase::update() {
    return true;
}

void DxLibUserInterfaceBase::draw() const {}

}  // namespace match_stick
