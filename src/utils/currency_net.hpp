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
#include <memory>
#include "section.h"
#include "spdlog/spdlog.h"

template<typename T>
struct HandleArray {
	HandleArray(cinatra::request& req, cinatra::response& res) : req(req), res(res) {}

	template<typename Item, typename Index>
	auto operator()(Item item, Index index) {
		constexpr auto idx = decltype( index )::value;

		if constexpr (std::is_same_v<std::decay_t<std::tuple_element_t<idx, T>>, cinatra::request>) {
			return &req;
		} else if constexpr (std::is_same_v<std::decay_t<std::tuple_element_t<idx, T>>, cinatra::response>) {
			return &res;
		} else if constexpr (std::is_same_v<std::decay_t<std::tuple_element_t<idx, T>>, std::string>) {
			std::string_view tmpSs = req.get_query_value(item);
			auto v = std::make_unique<std::string>(tmpSs);
			return std::move(v);
		} else {
			using tt = std::remove_reference_t<std::tuple_element_t<idx, T>>;
			auto v = std::make_unique<decltype( req.get_query_value<tt>(
				item) )>(req.get_query_value<tt>(item));
			return std::move(v);
		}
	}

private:
	cinatra::request& req;
	cinatra::response& res;
};

template<typename T>
struct type_return {
	constexpr static auto out(T t) {
		return t;
	}
};

template<typename T>
struct type_return<T*> {
	constexpr static auto out(T* t) {
		return *t;
	}
};

template<size_t ...N, typename Fun, typename Ob, typename Tup>
static void invokeOfTuple(const std::index_sequence<N...>&, Fun&& fun, Ob&& ob, Tup&& tup, cinatra::response& res) {
	if constexpr (std::is_same_v<member_return_t<Fun>, void>) {
		std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob),
			*std::get<N>(std::forward<Tup>(tup))...);
	} else {
		auto return_value = std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob),
			*std::get<N>(std::forward<Tup>(tup))...);
		if constexpr (std::is_same_v<std::decay_t<decltype( return_value )>, std::string>) {
			res.set_status_and_content(cinatra::status_type::ok, std::move(return_value));
		} else {
			res.set_status_and_content(cinatra::status_type::ok, std::move(std::to_string(return_value)));
		}
	}
}

template<size_t ...N, typename Fun, typename Ob>
static void invokeOfTuple(const std::index_sequence<N...>&, Fun&& fun, Ob&& ob, cinatra::response& res) {
	if constexpr (std::is_same_v<member_return_t<Fun>, void>) {
		std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob));
	} else {
		auto return_value = std::invoke(std::forward<Fun>(fun), std::forward<Ob>(ob));
		if constexpr (std::is_same_v<std::decay_t<decltype( return_value )>, std::string>) {
			res.set_status_and_content(cinatra::status_type::ok, std::move(return_value));
		} else {
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

template<size_t size, typename O, typename Tup>
static void joinNet_impl(O& o, cinatra::http_server& server, Tup&& vTuple) {

	auto to = std::get<size>(vTuple);

	spdlog::info("route: {}", std::get<0>(to));

	server.set_http_handler<std::decay_t< decltype( std::get<1>(to) )>::reqMethod>(std::get<0>(to),
		[&o, to](cinatra::request& req, cinatra::response& res) {
			auto fun = std::get<2>(to); //函数值
			//参数类型数量
			constexpr size_t args_size = std::tuple_size_v<member_args_t<decltype( fun )>>;
			//std::cout << "接收参数长度: " << args_size << std::endl;

			//宏里的参数数量
			constexpr size_t ss = std::tuple_size_v<decltype( to )>;
			//std::cout << "宏里参数长度: " << ss << std::endl;
			if constexpr (args_size == 0) {
				invokeOfTuple(std::make_index_sequence<args_size>(),
					fun,
					std::forward<O>(o),
					res
				);
			} else {
				std::array<std::string, args_size> array; //参数数组
				getNextValue<0, ss>(array, to);
				/*auto tup = a2t<hangArray_lambda, member_args_t<decltype( fun )>>(array, req, res);*/
				auto tup = a2t(array, HandleArray<member_args_t<decltype( fun )>>(req, res));
				invokeOfTuple(std::make_index_sequence<args_size>(),
					fun,
					std::forward<O>(o),
					tup,
					res
				);
			}
		}, log_t{});
}

template<typename O, typename Tup, size_t ...N>
void joinNet(O& o, cinatra::http_server& server, Tup&& tup, std::index_sequence<N...>) {
	( joinNet_impl<N>(o, server, std::forward<Tup>(tup)), ... );
}

template<typename O, typename ...T>
void execNet(O& o, cinatra::http_server& server, T ...t) {
	joinNet(o, server, std::make_tuple(t...), std::index_sequence_for<T...>());
}
