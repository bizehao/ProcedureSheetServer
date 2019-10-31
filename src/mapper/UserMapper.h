//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <vector>
#include "../entity/UserEntity.h"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"

//关于用户的sql操作
class UserMapper {
public:
    explicit UserMapper(ormpp::dbng<ormpp::mysql>& mysql):mysql(mysql){}

    std::vector<occupation> getOccupations();

private:
    ormpp::dbng<ormpp::mysql>& mysql;
};


