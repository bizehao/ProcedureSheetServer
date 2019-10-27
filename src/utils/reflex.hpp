#pragma once

#include <tuple>

//反射得到函数的参数类型

template <typename... Args>
using tuple_t = std::tuple<Args...>;

template <typename T, typename = std::void_t<>>
struct typeof {
	using type = T;
	static constexpr auto value = 0;
};

template <typename T>
struct typeof<T, std::void_t<typename T::type>> {
	using type = typename T::type;
	static constexpr auto value = 1;
};

template <typename T>
using typeof_t = typename typeof<T>::type;

template<typename T>
struct member_args;

template<typename T, typename U,typename... Args>
struct member_args<T (U::*)( Args... )> {
	using type = tuple_t<Args...>;
};

template<typename T>
using member_args_t = typeof_t<member_args<T>>;
