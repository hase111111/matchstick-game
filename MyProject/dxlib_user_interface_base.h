
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "dxlib_input.h"
#include "i_entity.h"

namespace match_stick {

class IDxLibInterface : public IEntity {
public:
    IDxLibInterface() = default;
    ~IDxLibInterface() = default;

    virtual bool isHovered(int mouse_x, int mouse_y) const = 0;

    virtual void callbackWhenClicked() = 0;

    virtual void callbackWhenHoverStarted() = 0;

    virtual void callbackWhenHoverEnded() = 0;
};

struct DxLibInterfaceDeployment final {
    enum class Direction {
        kUp,
        kDown,
        kLeft,
        kRight,
    };

    // 方向とその方向に配置するインターフェイスのid
    std::map<Direction, int> deployment_map;
};

class DxLibUserInterfaceBase final : IEntity {
public:
    DxLibUserInterfaceBase(const std::shared_ptr<const DxLibInput>& dxlib_input);
    ~DxLibUserInterfaceBase() = default;

    void registerInterface(const std::shared_ptr<IDxLibInterface>& dxlib_interface, int id);

    void registerInterfaceDeployment(const std::map<int, DxLibInterfaceDeployment>& deployment_map);

    void setDefaultSelectedId(const int id);

    bool update() override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    void draw() const override {};

private:
    static constexpr int kNoSelectedId = -1;

    bool validateDeploymentMap() const;

    void updateSelectedIdWhenMouseUsed();

    void updateSelectedIdWhenKeyboardUsed();


    std::map<int, std::shared_ptr<IDxLibInterface>> dxlib_interfaces_;

    std::map<int, DxLibInterfaceDeployment> deployment_map_;

    const std::shared_ptr<const DxLibInput> dxlib_input_;

    int default_selected_id_{ kNoSelectedId };

    int selected_id_{ kNoSelectedId };
};

}  // namespace match_stick
