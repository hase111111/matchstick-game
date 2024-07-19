#pragma once

#include <map>
#include <vector>
#include <string>
#include"MatchGameCommon.h"

class Parameter
{
public:
    const static int Error = -1;

    Parameter() = default;
    virtual ~Parameter() = default;

    void setParam(std::string key, int val);
    int  getParam(std::string key) const;

    void setFieldParam(const std::vector<MatchField>& _data);
    void getFieldParam(std::vector<MatchField>& _data) const;

    void resetParam();

private:
    std::map<std::string, int> _map;
    std::vector<MatchField> _field;
};
