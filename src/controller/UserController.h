//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "../utils/section.h"
#include "../utils/currency_net.hpp"
#include "../mapper/UserMapper.h"
#include "../base/BaseController.hpp"

class UserController : BaseController {
public:
    UserController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {}

    void exec() override;

private:

    std::string hello1(cinatra::request& req, cinatra::response& res);

    std::string hello2(int& a);
};
