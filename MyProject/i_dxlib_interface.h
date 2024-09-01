
#pragma once

namespace match_stick {

class IDxLibInterface {
public:
    IDxLibInterface() = default;
    ~IDxLibInterface() = default;

    virtual bool isHovered(int mouse_x, int mouse_y) const = 0;

    virtual void callbackWhenClicked() = 0;

    virtual void callbackWhenHoverStarted() = 0;

    virtual void callbackWhenHoverEnded() = 0;
};

}  // namespace match_stick