#pragma once

#include <tuple>
#include <functional>

//反射得到成员方法的参数列表

template<typename... Args>
using tuple_t = std::tuple<Args...>;

template<typename T, typename = std::void_t<>>
struct type_method {
    using type = T;
    static constexpr auto value = 0;
};

template<typename T>
struct type_method<T, std::void_t<typename T::type>> {
    using type = typename T::type;
    static constexpr auto value = 1;
};

template<typename T>
using type_method_t = typename type_method<T>::type;

template<typename T>
struct member_args;

template<typename T, typename U, typename... Args>
struct member_args<T (U::*)(Args...)> {
    using type = tuple_t<Args...>;
};

template<typename T>
using member_args_t = type_method_t<member_args<T>>;

/////////////////////////////////////////////////////////////////////////////////////

/*template<template<typename index> typename Fun, typename Array, std::size_t... I>
auto a2t_impl(const Array& a, std::index_sequence<I...>){

};*/

template<typename F>
constexpr size_t pp(F f) {
    return f();
}

template<size_t index, typename T>
class hangArray_lambda {
public:
    explicit hangArray_lambda(cinatra::request& req) : req(req) {}

    auto operator()(const std::string& v) const {
        std::cout << "  " << v << std::endl;
        return req.get_query_value<std::tuple_element_t<index, T>>(v);
    }

private:
    cinatra::request& req;
};

// 转换数组为 tuple时 给每个数组元素加上另一个对应数组元素的值
template<template<size_t, typename> typename Fun, typename TupType, typename Array, size_t... I>
auto a2t_impl(const Array& a, cinatra::request& req, std::index_sequence<I...>) {
    return std::make_tuple(Fun<I, TupType>(req)(a[I])...);
}


template<template<size_t, typename> typename Fun,typename TupType, typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a, cinatra::request& req) {
    return a2t_impl<Fun,TupType>(a, req, Indices{});
}
