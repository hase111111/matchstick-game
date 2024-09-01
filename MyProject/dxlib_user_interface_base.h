
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "dxlib_input.h"
#include "i_dxlib_user_interface.h"
#include "i_entity.h"

namespace match_stick {

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

    void registerInterface(const std::shared_ptr<IDxLibUserInterface>& dxlib_interface, int id);

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


    std::map<int, std::shared_ptr<IDxLibUserInterface>> dxlib_interfaces_;

    std::map<int, DxLibInterfaceDeployment> deployment_map_;

    const std::shared_ptr<const DxLibInput> dxlib_input_;

    int default_selected_id_{ kNoSelectedId };

    int selected_id_{ kNoSelectedId };
};

}  // namespace match_stick
