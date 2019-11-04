//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <vector>
#include "../entity/UserEntity.h"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "../base/BaseMapper.hpp"

//==sql==
class UserMapper : BaseMapper {
public:
    explicit UserMapper(ormpp::dbng<ormpp::mysql>& mysql) : BaseMapper(mysql) {}

    std::vector<bzh::User> getUserByName();

};


