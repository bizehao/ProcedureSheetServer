//
// Created by bizehao on 2019/10/26.
//
#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include <functional>
#include "reflex.hpp"
#include <array>

template<size_t ...N, typename Fun, typename Ob, typename Tup>
static void invokeOfTuple(const std::index_sequence<N...>&, Fun&& fun, Ob&& ob, Tup&& tup, cinatra::response& res) {
    if constexpr (std::is_same_v<member_return_t<Fun>, void>) {
        std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob), std::get<N>(std::forward<Tup>(tup))...);
    } else {
        auto return_value = std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob), std::get<N>(std::forward<Tup>(tup))...);
        if constexpr(std::is_same_v<std::decay_t<decltype(return_value)>, std::string>) {
            res.set_status_and_content(cinatra::status_type::ok, std::move(return_value));
        } else{
            res.set_status_and_content(cinatra::status_type::ok, std::move(std::to_string(return_value)));
        }
    }
}

//元祖大小 数组大小 下标值 0  5  3
template<size_t N, size_t CN, size_t AN, typename Tup>
static auto getNextValue(std::array<std::string, AN>& array, Tup&& tup) {
    if constexpr (N < AN - 1) {
        getNextValue<N + 1, CN>(array, tup);
    }
    array[N] = std::get<CN - AN + N>(tup);
}

template<size_t size, typename O, typename ...T>
static void joinNet(O& o, cinatra::http_server& server, const std::tuple<T...>& vTuple) {
    if constexpr (size > 0) {
        joinNet<size - 1>(o, server, vTuple);
    }
    auto to = std::get<size>(vTuple);
    std::cout << "请求头: " << std::get<size>(to) << std::endl;
    server.set_http_handler<cinatra::GET>(std::get<0>(to),
                                          [&o, to](cinatra::request& req, cinatra::response& res) {
                                              auto fun = std::get<1>(to); //函数值
                                              //参数类型数量
                                              constexpr size_t args_size = std::tuple_size_v<member_args_t<decltype(fun)>>;
                                              //std::cout << "接收参数长度: " << args_size << std::endl;
                                              using sas = std::tuple_element_t<0, member_args_t<decltype(fun)>>;

                                              //宏里的参数数量
                                              constexpr size_t ss = std::tuple_size_v<decltype(to)>;
                                              //std::cout << "宏里参数长度: " << ss << std::endl;
                                              std::array<std::string, args_size> array; //参数数组
                                              getNextValue<0, ss>(array, to);
                                              auto tup = a2t<hangArray_lambda, member_args_t<decltype(fun)>>(array, req,
                                                                                                             res);
                                              invokeOfTuple(std::make_index_sequence<args_size>(),
                                                            fun,
                                                            std::forward<O>(o),
                                                            tup,
                                                            res
                                              );
                                          });
}

template<typename O, typename ...T>
void execNet(O& o, cinatra::http_server& server, T ...t) {
    joinNet<sizeof...(t) - 1>(o, server, std::make_tuple(t...));
}

