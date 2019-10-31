//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include "../utils/section.h"
#include <functional>
#include <ormpp/mysql.hpp>
#include <ormpp/dbng.hpp>
#include "../utils/currency_net.hpp"
#include "../mapper/UserMapper.h"

class UserController {
public:
    UserController(cinatra::http_server& server, UserMapper& userMapper) : server(server), userMapper(userMapper) {}

    void exec();

private:

    std::string hello1(cinatra::request& req, cinatra::response& res);

    //int& a, int& b,
    std::string hello2(int a);

    cinatra::http_server& server;
    UserMapper& userMapper;
};
