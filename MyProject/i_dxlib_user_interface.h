
#pragma once

namespace match_stick {

class IDxLibUserInterface {
public:
    IDxLibUserInterface() = default;
    ~IDxLibUserInterface() = default;

    virtual bool isHovered(int mouse_x, int mouse_y) const = 0;

    virtual void initHoverState(bool is_hovered) = 0;

    virtual void callbackWhenClicked() = 0;

    virtual void callbackWhenHoverStarted() = 0;

    virtual void callbackWhenHoverEnded() = 0;
};

}  // namespace match_stick