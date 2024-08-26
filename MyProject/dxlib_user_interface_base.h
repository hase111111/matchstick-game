
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "i_entity.h"

namespace match_stick {

class IDxLibInterface : public IEntity {
public:
    enum class InterfaceType {
        kNormalButton,
        kToggleButton,
    };

    IDxLibInterface() = default;
    ~IDxLibInterface() = default;

    virtual bool isHovered(int left_x, int top_y, int right_x, int bottom_y) const = 0;

    virtual InterfaceType getInterfaceType() const = 0;
};

class DxLibUserInterfaceBase final : IEntity {
public:
    DxLibUserInterfaceBase() = default;
    ~DxLibUserInterfaceBase() = default;

    void registerInterface(const std::shared_ptr<IDxLibInterface>& dxlib_interface, int id);

    void registerInterfaceDeployment(const std::map<int, std::vector<int>>& deployment_map);

    bool update() override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    void draw() const override;

private:
    std::map<int, std::shared_ptr<IDxLibInterface>> dxlib_interfaces_;

    std::map<int, std::vector<int>> deployment_map_;

    int selected_id_ = -1;
};

}  // namespace match_stick
