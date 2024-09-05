
#pragma once

#include "i_dxlib_user_interface.h"
#include "i_scene.h"

namespace match_stick {

class SoundChangeBar final : public IDxLibUserInterface, public IScene {
public:
    SoundChangeBar(int x, int y, int default_value);
    ~SoundChangeBar() = default;

    bool update() override;

    void draw() const override;

    void onStart(const SceneChangeParameter&) override {};

    void onReturnFromOtherScene(const SceneChangeParameter&) override {};

    bool isHovered(int mouse_x, int mouse_y) const;

    void initHoverState(bool is_hovered);

    void callbackWhenClicked();

    void callbackWhenHoverStarted();

    void callbackWhenHoverEnded();
};

}  // match_stick
