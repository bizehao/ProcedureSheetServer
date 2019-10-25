//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include "cinatra.hpp"
#include "../utils/section.h"
#include <tuple>

class UserController {
public:
    void exec(cinatra::http_server &server);

private:
    void hello1(cinatra::request& req, cinatra::response& res);
    constexpr void hello2(cinatra::request& req, cinatra::response& res);
};

    void hello1(cinatra::request &req, cinatra::response &res);

    void hello2(cinatra::request &req, cinatra::response &res);
};
