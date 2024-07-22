
#pragma once

#include "scene_change_parameter.h"

namespace match_stick
{

//! @brief シーンのインターフェース．
class IScene
{
public:
    virtual ~IScene() = default;

    //! @brief シーンの更新処理．
    //! @return ゲームを続けるかどうか．
    virtual bool Update() = 0;

    //! @brief シーンの描画処理．
    virtual void Draw() const = 0;

    //! @brief シーンが開始されたときに呼び出される関数．
    virtual void OnStart(const SceneChangeParameter& parameter) = 0;

    //! @brief 別のシーンから戻ってきたときに呼び出される関数．
    virtual void OnReturnFromOtherScene(const SceneChangeParameter& parameter) = 0;
};

}  // namespace match_stick
