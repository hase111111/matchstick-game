
#pragma once

namespace match_stick {

template <typename T>
class MathConst final {};

template <>
class MathConst<float> final {
public:
    static constexpr float kPi = 3.14159265358979323846f;
    static constexpr float kE = 2.71828182845904523536f;
};

template <>
class MathConst<double> final {
public:
    static constexpr double kPi = 3.14159265358979323846;
    static constexpr double kE = 2.71828182845904523536;
};

}  // namespace match_stick
