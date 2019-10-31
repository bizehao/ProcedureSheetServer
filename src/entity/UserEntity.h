//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <string>
#include "ormpp/reflection.hpp"

//用户类型表
struct occupation {
    int id;
    std::string occupation_name;
};
REFLECTION(occupation, id, occupation_name)
