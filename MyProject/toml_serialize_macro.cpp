﻿
#include "toml_serialize_macro.h"

namespace match_stick::toml_func
{

const char Toml11Description::kNoTable[] = "no_table_value";

std::vector<std::string> sjis_to_utf8_vec(const std::vector<std::string>& str_vec)
{
    std::vector<std::string> ret_vec;
    for (const auto& str : str_vec)
    {
        ret_vec.push_back(sjis_to_utf8(str));
        // ret_vec.push_back(str);
    }
    return ret_vec;
}


}  // namespace match_stick::toml_func
