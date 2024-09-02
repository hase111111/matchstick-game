
#pragma once

#include <map>
#include <memory>
#include <vector>

#include "dxlib_input.h"
#include "i_dxlib_user_interface.h"
#include "i_entity.h"

namespace match_stick {

struct DxLibUIDeployment final {
    struct DirectionMap {
        int up_id{ -1 };
        int down_id{ -1 };
        int left_id{ -1 };
        int right_id{ -1 };
    };

    // UI の id と，その id の UI から移動できる UI
    std::map<int, DirectionMap> id_to_direction_map;
};

class DxLibUserInterfaceBase final : public IEntity {
public:
    explicit DxLibUserInterfaceBase(const std::shared_ptr<const DxLibInput>& dxlib_input);
    ~DxLibUserInterfaceBase() = default;

    void registerInterface(const std::shared_ptr<IDxLibUserInterface>& dxlib_interface, int id);

    void registerInterfaceDeployment(int target_id, int up_id, int down_id, int left_id, int right_id);

    void setDefaultSelectedId(const int id);

    bool update() override;

    int getLayer() const override {
        return constants::kUIFrontLayer;
    }

    void draw() const override {};

private:
    static constexpr int kNoSelectedId = -1;


    void updateSelectedIdWhenMouseUsed();

    void updateSelectedIdWhenKeyboardUsed();


    std::map<int, std::shared_ptr<IDxLibUserInterface>> dxlib_interfaces_;

    DxLibUIDeployment ui_deployment_;

    const std::shared_ptr<const DxLibInput> dxlib_input_;

    int default_selected_id_{ kNoSelectedId };

    int selected_id_{ kNoSelectedId };
};

}  // namespace match_stick
