
#pragma once

#include "scene_change_parameter.h"
#include "scene_name.h"

namespace match_stick {

class SceneChangeListener final
{
public:
    enum class RequestType
    {
        kNone,
        kAddScene,
        kDeleteScene,
        kDeleteAllScene
    };

    void RequestAddScene(SceneName scene_name, const SceneChangeParameter& parameter);
    void RequestDeleteScene(int delete_num, const SceneChangeParameter& parameter);
    void RequestDeleteAllScene();

    bool HasRequest() const;

    //! @brief リクエストを受け取る．
    //! 受け取った後，リクエストはリセットされる．
    //! リクエストがない場合は何もしない．
    //! @param[out] scene_name シーン名．
    //! @param[out] parameter パラメータ．
    //! @param[out] delete_num 削除するシーンの数．
    //! @return リクエストの種類．
    RequestType ReceiveRequest(SceneName* scene_name, SceneChangeParameter* parameter, int* delete_num);

private:
    SceneName scene_name_{ SceneName::kTitle };
    SceneChangeParameter parameter_{};
    int delete_num_{ 0 };

    bool has_request_{ false };
    RequestType request_type_{ RequestType::kNone };
};

}  // namespace match_stick
