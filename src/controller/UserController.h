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
    template<typename ...M>
    void exec(cinatra::http_server &server, M ...m) {
        auto tuple = std::make_tuple(m...);
        auto a = std::index_sequence_for<M...>();
        auto mm = {0,server.set_http_handler<cinatra::GET>(static_cast<std::string>(m), [this](cinatra::request& req, cinatra::response& res) {
            this->hello1(req,res);
        },log_t{})...};
    };

    void hello1(cinatra::request &req, cinatra::response &res);

    void hello2(cinatra::request &req, cinatra::response &res);
};
