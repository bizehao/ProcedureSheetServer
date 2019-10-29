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

//第一个请求头  第二个请求的方法地址  剩余的为参数字段名
#define SV(...) std::make_tuple(__VA_ARGS__)

class UserController {
public:
    void exec(cinatra::http_server& server);

private:

    void hello1(cinatra::request& req, cinatra::response& res);

    std::string hello2(int& a, int& b, cinatra::request* req,cinatra::response* res);
};
