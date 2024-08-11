
#pragma once

#include <memory>
#include <string>

#include "dxlib_input.h"
#include "i_entity.h"

namespace match_stick {

class LanguageUI final : public IEntity {
public:
    LanguageUI(const std::shared_ptr<const DxLibInput>& dxlib_input);
    ~LanguageUI() = default;

    inline int getLayer() const override {
        return constants::kBackGroundLayer;
    }

    bool update() override;

    void draw() const override;

private:
    void updateSelectIndex();

    void drawButton() const;

    void drawTable() const;

    const std::shared_ptr<const DxLibInput> dxlib_input_;

    const std::string attention_str_{ "Attention: After the change, "
                                      "you need to go back to the title to update the text." };

    int select_index_x_{ 0 }, select_index_y_{ 0 };
};

}  // namespace match_stick
