//
// Created by bizehao on 2019/10/31.
//

#include "UserMapper.h"
#include "../utils/currency_sql.hpp"

std::vector<Occupation> UserMapper::getUserByName() {
    return bzh::customizeQuery<Occupation>(mysql, "select * from occupation");
}
