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

#define SV(name, server) std::make_tuple(name,server)

class UserController {
public:
    void exec(cinatra::http_server &server);

private:

    void hello1(cinatra::request &req, cinatra::response &res);

    void hello2(cinatra::request &req, cinatra::response &res);
};
