#include "Parameter.h"

void Parameter::setParam(std::string key, int val)
{
    _map[key] = val;
}

int Parameter::getParam(std::string key) const
{
    auto it = _map.find(key);   //指定キーを取得
    if (_map.end() == it) {     //無かったら
        return Error;           //エラー
    }
    else {
        return it->second;      //あったら値を返す
    }
}

void Parameter::setFieldParam(const std::vector<MatchField>& _data)
{
    //フィールドを空にする
    _field.clear();

    //引数を挿入する
    for (auto &i : _data)
    {
        _field.push_back(i);
    }
}

void Parameter::getFieldParam(std::vector<MatchField>& _data) const
{
    //フィールドを空にする
    _data.clear();

    //引数を挿入する
    for (auto& i : _field)
    {
        _data.push_back(i);
    }
}

void Parameter::resetParam()
{
    _map.clear();
    _field.clear();
}
