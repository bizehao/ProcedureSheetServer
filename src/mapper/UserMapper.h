//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <vector>
#include "../entity/UserEntity.h"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "../base/BaseMapper.hpp"

//关于用户的sql操作
class UserMapper : BaseMapper {
public:
    explicit UserMapper(ormpp::dbng<ormpp::mysql>& mysql) : BaseMapper(mysql) {}

    //根据用户名获取用户
    std::vector<Occupation> getUserByName();

};


