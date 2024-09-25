#include "Parameter.h"

void Parameter::setParam(std::string key, int val)
{
    _map[key] = val;
}

int Parameter::getParam(std::string key) const
{
    auto it = _map.find(key);   //�w��L�[���擾
    if (_map.end() == it) {     //����������
        return Error;           //�G���[
    }
    else {
        return it->second;      //��������l��Ԃ�
    }
}

void Parameter::setFieldParam(const std::vector<MatchField>& _data)
{
    //�t�B�[���h����ɂ���
    _field.clear();

    //������}������
    for (auto &i : _data)
    {
        _field.push_back(i);
    }
}

void Parameter::getFieldParam(std::vector<MatchField>& _data) const
{
    //�t�B�[���h����ɂ���
    _data.clear();

    //������}������
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
