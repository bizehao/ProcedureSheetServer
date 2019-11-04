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

	void exec() override {
		execNet(*this,
			server,
			SV("/login", HttpPost{}, &UserController::login, "username", "password")
		);
	};

private:

	/**
	 * 登录
	 * 返回用户的id,
	 */
	std::string login(std::string& username, std::string& password) {
		std::cout << "join hello2: " << std::endl;
		auto pp = userMapper.getUserByName();
		std::string ms = "login successfully";
		if (pp.size() < 0) {
			if (pp[0].username != username) {
				ms = "user does not exist";
			} else {
				ms = "password error";
			}
		}
		return bzh::conversionJson<bzh::status::success>(ms);
	};

	//注册
	std::string regist(){
		return "as";
	}


};
