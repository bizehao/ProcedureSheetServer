//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include "../utils/section.h"
#include <functional>

#define SV(name, server) std::make_tuple(name,server)

class UserController {
public:
    void exec(cinatra::http_server &server);

private:

    template<typename ...T>
    void exec(cinatra::http_server &server, T ...t) {
        lineOut<sizeof...(t) - 1>(server, std::make_tuple(t...));
    }

    template<size_t N, typename ...T>
    void lineOut(cinatra::http_server &server, const std::tuple<T...> &vTuple) {
        if constexpr (N > 0) {
            lineOut<N - 1>(server, vTuple);
        }
        auto o = std::get<N>(vTuple);
        std::cout << std::get<0>(o) << std::endl;
        server.set_http_handler<cinatra::GET>(std::get<0>(o),
                                              [this, o](cinatra::request &req, cinatra::response &res) {
                                                  std::invoke(std::get<1>(o), this, req, res);
                                              });
    }

    void hello1(cinatra::request &req, cinatra::response &res);

    void hello2(cinatra::request &req, cinatra::response &res);

    void test(int xx) {
        std::cout << "test: " << xx << std::endl;
    }
};
