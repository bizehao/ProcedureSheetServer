//
// Created by bizehao on 2019/10/26.
//
#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include <functional>

template<size_t size, typename O, typename ...T>
static void joinNet(O &o, cinatra::http_server &server, const std::tuple<T...> &vTuple) {
    if constexpr (size > 0) {
        joinNet<size - 1>(o, server, vTuple);
    }
    auto to = std::get<size>(vTuple);
    std::cout << std::get<0>(to) << std::endl;
    server.set_http_handler<cinatra::GET>(std::get<0>(to),
                                          [&o, to](cinatra::request &req, cinatra::response &res) {
                                              std::invoke(std::get<1>(to), std::forward<O>(o), req, res);
                                          });
}

template<typename O, typename ...T>
void execNet(O &o, cinatra::http_server &server, T ...t) {
    joinNet<sizeof...(t) - 1>(o, server, std::make_tuple(t...));
}