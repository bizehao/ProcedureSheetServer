//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "../utils/section.h"
#include "../base/BaseController.hpp"

class UserController : BaseController {
public:
    UserController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {}

	void exec() override;

private:

	/**
	 * 登录
	 * 返回用户的id,
	 */
	std::string login(std::string& username, std::string& password);

	//注册
	std::string regist();
};
