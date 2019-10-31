//
// Created by bizehao on 2019/10/31.
//

#include "UserMapper.h"
#include "../utils/currency_sql.hpp"

std::vector<occupation> UserMapper::getOccupations() {
    return bzh::customizeQuery<occupation>(mysql, "select * from occupation");
}
