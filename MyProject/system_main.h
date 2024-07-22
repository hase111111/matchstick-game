
#pragma once

namespace match_stick {

class SystemMain final
{
public:
    SystemMain() = default;
    ~SystemMain() = default;

    bool initialize() const;
    void finalize() const;
    void main() const;
};

}  // namespace match_stick
