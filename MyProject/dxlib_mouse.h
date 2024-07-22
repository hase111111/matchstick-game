
#pragma once

#include <array>
#include <map>

namespace match_stick
{

class DxLibMouse final {

public:
    DxLibMouse();

    //! @brief マウス入力を更新する．これを毎フレーム実行しないと，
    //! マウス入力を取得できない．
    void update();

    //! @brief ボタンが押されているフレーム数を取得する．
    //! @param[in] mouse_code どのボタンを調べたいか．
    //! @n 例えば右クリックだったら，MOUSE_INPUT_RIGHTとなる．
    //! @return 押されているフレーム数．
    //! 異常な mouse_code が渡された場合は - 1を返す．
    [[nodiscard]] int getPressingCount(int mouse_code) const;

    //! @brief ボタンが離されているフレーム数を取得する．
    //! @param[in] mouseCode どのボタンを調べたいか．
    //! @n 例えば右クリックだったら，MOUSE_INPUT_RIGHT となる．
    //! @return 離されているフレーム数．
    //! 異常な mouse_code が渡された場合は-1を返す．
    [[nodiscard]] int getReleasingCount(int mouse_code) const;

    //! @brief マウスカーソルの位置を取得する．
    //! X座標は画面の左端を0として，右向きが正．
    //! これは Dxlib の仕様なので変更不能．
    //! @return マウスカーソルのX座標．
    [[nodiscard]] constexpr int GetCursorPosX() const noexcept {
        return cursor_pos_x_;
    };

    //! @brief マウスカーソルの移動量を取得する．
    //! X座標は画面の左端を0として，右向きが正．
    //! これは Dxlib の仕様なので変更不能．
    //! @return マウスカーソルのX方向の移動量．
    [[nodiscard]] int getDiffPosX() const;

    //! @brief マウスカーソルの位置を取得する．
    //! Y座標は画面の上端を0として，下向きが正．
    //! これは Dxlib の仕様なので変更不能．
    //! @return マウスカーソルのY座標．
    [[nodiscard]] constexpr int getCursorPosY() const noexcept {
        return cursor_pos_y_;
    };

    //! @brief マウスカーソルの移動量を取得する．
    //! Y座標は画面の上端を0として，下向きが正．
    //! これは Dxlib の仕様なので変更不能．
    //! @return マウスカーソルのY方向の移動量．
    [[nodiscard]] int getDiffPosY() const;

    //! @brief マウスカーソルの移動量を取得する．
    //! @return double マウスカーソルの移動量．
    [[nodiscard]] double getDiffPos() const;

    //! @brief マウスのホイールの回転量を取得する．
    //! @n 1フレームで回転した量を取得する．
    //! @n 手前に回した分はマイナスの値として、
    //! 奥に回した分はプラスの値として返る
    //! @return int マウスホイールの回転量．
    [[nodiscard]] constexpr int getWheelRot() const noexcept {
        return wheel_rot_;
    };

private:
    //! マウスのボタンの数．右・左・中央 + 5つのボタン．
    constexpr static int kMouseKeyNum{ 8 };

    //! マウスのボタンのキーコード．
    const std::array<int, kMouseKeyNum> kMouseKeyCodes;

    //! マウスカーソルの位置．
    int cursor_pos_x_, cursor_pos_y_;

    //! 1フレーム前のマウスカーソルの位置．
    int cursor_past_pos_x_, cursor_past_pos_y_;


    //! マウスのボタンが押され続けているフレーム数．
    std::map<int, int> pushing_counter_;

    //! マウスのボタンが離され続けているフレーム数．
    std::map<int, int> releasing_counter_;

    //! マウスホイールの回転量，
    //! 手前に回した分はマイナスの値として、奥に回した分はプラスの値として返る．
    int wheel_rot_;
};

}  // namespace match_stick
