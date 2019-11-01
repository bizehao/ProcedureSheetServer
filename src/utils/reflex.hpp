#pragma once

#include <tuple>
#include <functional>

//反射得到成员方法的参数列表

template<typename... Args>
using tuple_t = std::tuple<Args...>;

template<typename T, typename = std::void_t<>>
struct type_method_args {
    using type = T;
    static constexpr auto value = 0;
};

template<typename T>
struct type_method_args<T, std::void_t<typename T::args_type>> {
    using type = typename T::args_type;
    static constexpr auto value = 1;
};

template<typename T, typename = std::void_t<>>
struct type_method_return {
    using type = T;
    static constexpr auto value = 0;
};

template<typename T>
struct type_method_return<T, std::void_t<typename T::return_type>> {
    using type = typename T::return_type;
    static constexpr auto value = 1;
};

template<typename T>
using type_method_args_t = typename type_method_args<T>::type;

template<typename T>
using type_method_return_t = typename type_method_return<T>::type;

template<typename T>
struct member_args_return;

template<typename T, typename U, typename... Args>
struct member_args_return<T(U::*)(Args...)> {
    using args_type = tuple_t<Args...>;
    using return_type = T;
};

template<typename T>
using member_args_t = type_method_args_t<member_args_return<T>>;

template<typename T>
using member_return_t = type_method_return_t<member_args_return<T>>;

/////////////////////////////////////////////////////////////////////////////////////

// 转换数组为 tuple时 给每个数组元素加上另一个对应数组元素的值
template<typename Array, typename Fun, size_t... I>
auto a2t_impl(const Array& a, Fun&& func, std::index_sequence<I...>) {
    return std::make_tuple(func(a[I], std::integral_constant<size_t, I>{})...);
}

//数组转tuple
template<typename T, std::size_t N, typename Fun, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a, Fun&& funv) {
    return a2t_impl(a, funv, Indices{});
}

//tuple转tuple impl
/*template<typename Tup, size_t... I>
auto t2t_impl(Tup&& tup, std::index_sequence<I...>) {
	return std::make_tuple(Fun<I, TupType>(req, res)(a[I])...);
}

//tuple转tuple
template<typename Tup, typename Indices = std::make_index_sequence<std::tuple_size_v<Tup>>>
auto t2t(Tup&& tup) {
	return t2t_impl(tup, Indices{});
}*/
