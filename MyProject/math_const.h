
//! @file math_const.h
//! @brief
//! Copyright(c) 2024 Taisei Hasegawa
//! Released under the MIT license
//! https://opensource.org/licenses/mit-license.php

#pragma once

namespace match_stick {

//! @class MathConst
//! @brief 数学定数を格納するクラス．
//! テンプレート引数によって float 型と double 型の定数を定義する．
//! それ以外はインスタンス化せず，ここにくる．
template <typename T>
class MathConst final {};

//! @brief float型の数学定数を定義する．
template <>
class MathConst<float> final {
public:
    static constexpr float kPi = 3.14159265358979323846f;
    static constexpr float kE = 2.71828182845904523536f;
};

//! @brief double型の数学定数を定義する．
template <>
class MathConst<double> final {
public:
    static constexpr double kPi = 3.14159265358979323846;
    static constexpr double kE = 2.71828182845904523536;
};

}  // namespace match_stick
