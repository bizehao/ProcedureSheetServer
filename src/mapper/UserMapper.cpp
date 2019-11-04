//
// Created by bizehao on 2019/10/31.
//

#include "UserMapper.h"
#include "../utils/currency_sql.hpp"

std::vector<bzh::User> UserMapper::getUserByName() {
	return bzh::customizeQuery<bzh::User>(mysql, "select id,username,password,email,type,phone,lately_date,ip_address from users");
}
