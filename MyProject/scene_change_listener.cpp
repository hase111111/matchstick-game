
#include "scene_change_listener.h"

#include "dxlib_assert.h"


namespace match_stick
{

void SceneChangeListener::requestAddScene(const SceneName scene_name, const SceneChangeParameter& parameter)
{
    // リクエストを設定する．
    has_request_ = true;
    request_type_ = RequestType::kAddScene;

    // パラメータを設定する．
    scene_name_ = scene_name;
    parameter_ = parameter;
}

void SceneChangeListener::requestDeleteScene(const int delete_num, const SceneChangeParameter& parameter)
{
    // リクエストを設定する．
    has_request_ = true;
    request_type_ = RequestType::kDeleteScene;

    // パラメータを設定する．
    parameter_ = parameter;
    delete_num_ = delete_num;
}

void SceneChangeListener::requestDeleteAllScene()
{
    // リクエストを設定する．
    has_request_ = true;
    request_type_ = RequestType::kDeleteAllScene;
}

bool SceneChangeListener::hasRequest() const
{
    return has_request_;
}

SceneChangeListener::RequestType SceneChangeListener::receiveRequest(SceneName* scene_name, SceneChangeParameter* parameter, int* delete_num)
{
    // 引数が nullでないかチェックする．
    ASSERT_NOT_NULL_PTR(scene_name);
    ASSERT_NOT_NULL_PTR(parameter);
    ASSERT_NOT_NULL_PTR(delete_num);

    // リクエストがない場合は何もしない．
    if (!has_request_)
    {
        return RequestType::kNone;
    }

    // リクエストを受け取る．
    *scene_name = scene_name_;

    *parameter = parameter_;

    *delete_num = delete_num_;

    RequestType ret = request_type_;

    // リクエストをリセットする．
    has_request_ = false;
    request_type_ = RequestType::kNone;

    return ret;
}

}  // namespace match_stick
