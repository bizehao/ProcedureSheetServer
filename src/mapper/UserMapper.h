//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <vector>
#include "../entity/UserEntity.h"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "../base/BaseMapper.hpp"
#include <optional>

//==sql==
class UserMapper : BaseMapper {
public:
	explicit UserMapper(ormpp::dbng<ormpp::mysql>& mysql) : BaseMapper(mysql) {}

	//获取用户通过名字
	std::vector<bzh::User> getUserByName(std::string& username);

	//修改用户的登录时间
	bool updateLoginTM(std::string& username, std::string& datetime);

	//获取email是否在用户中以使用
	std::optional<int> getCountByEmail(std::string& email);

	//获取username是否在用户中以使用
	std::optional<int> getCountByUsername(std::string& email);

	//添加用户
	bool insertUser(std::string& username, std::string& password, std::string& email, int& type);

	//获取语言列表
	std::vector<bzh::LanguageType> getLanguageList();
};


