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
static void invokeOfTuple(const std::index_sequence<N...>&, Fun& fun, Ob ob, Tup& tup) {
	std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob), std::get<N>(tup)...);
}

//元祖大小 数组大小 下标值 4  2  0
template<size_t N, size_t CN, size_t AN, typename Tup>
static auto getNextValue(std::array<std::string, AN>& array, Tup& tup) {
	if constexpr (N + AN < CN - 1) {
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
	std::cout << std::get<0>(to) << std::endl;
	server.set_http_handler<cinatra::GET>(std::get<0>(to),
		[&o, to](cinatra::request& req, cinatra::response& res) {
			auto xx = std::get<1>(to); //函数值
			constexpr size_t args_size = std::tuple_size_v<member_args_t<decltype( xx )>>;
			std::cout << args_size << std::endl;

			constexpr auto ss = std::tuple_size_v<decltype( to )>; //参数长度
			std::cout << "参数长度" << ss << std::endl;
			std::array<std::string, ss - 2> array; //参数数组
			getNextValue<0, ss>(array, to);

			//int a = req.get_query_value<int>(array[0]);
			//int b = req.get_query_value<int>(array[1]);
			auto tup = a2t<hangArray_lambda, member_args_t<decltype( xx )>>(array, req);

			/*auto tup = a2t(array, [&req](auto index,const std::string& v) {
				std::cout << v << std::endl;
				return req.get_query_value<std::tuple_element_t<index, member_args_t<decltype( xx )>>>(v);
			});*/
			invokeOfTuple(std::make_index_sequence<2>(),
				std::get<1>(to),
				std::forward<O>(o),
				tup
			);
		});
}

template<typename O, typename ...T>
void execNet(O& o, cinatra::http_server& server, T ...t) {
	joinNet<sizeof...( t ) - 1>(o, server, std::make_tuple(t...));
}

