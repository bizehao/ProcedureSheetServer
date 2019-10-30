//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include "../utils/section.h"
#include <functional>
#include "../utils/currency_net.hpp"

class UserController {
public:
	void exec(cinatra::http_server& server);

private:

    std::string hello1(cinatra::request& req, cinatra::response& res);

	//int& a, int& b,
	std::string hello2(cinatra::request& req, cinatra::response& res, int& a, int& b);
};
