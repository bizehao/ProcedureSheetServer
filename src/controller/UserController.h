//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "cinatra.hpp"
#include "../utils/section.h"

class UserController {
public:
	void exec(cinatra::http_server& server);

private:
	template<typename ...T>
	void exec(T ...t) {
		std::tuple<T...> vTuple = std::make_tuple(t...);
		lineOut1(std::index_sequence_for<T...>());
		lineOut2<sizeof...( t )-1>();
		lineOut2<std::tuple_size_v<std::tuple<T...>>>();
	}

	template<int... N>
	void lineOut1(std::index_sequence<N...>) {
		using Dummy = int[];
		static_cast<void>( Dummy{ ( std::cout << N << std::endl, 0 )... } );
	}

	template<int N>
	void lineOut2() {
		if constexpr (N > 0) {
			lineOut2<N - 1>();
		}
		std::cout << N << std::endl;
	}

	void hello1(cinatra::request& req, cinatra::response& res);
	void hello2(cinatra::request& req, cinatra::response& res);
};
