// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"
#include "cinatra.hpp"
#include "utils/reflex.hpp"
#include <functional>
#include <iostream>
#include <tuple>
#include <array>

struct Test {
public:
    Test() {}

    void say(int a, double b) {
        std::cout << a << b << std::endl;
    }
};

/*template<typename Fun, typename Array, std::size_t... I>
auto a2t_impl(const Array& a, Fun fun, std::index_sequence<I...>) {
    return std::make_tuple(fun(a[I])...);
}

template<typename Fun, typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& a, Fun fun) {
    return a2t_impl(a, std::forward<Fun>(fun), Indices{});
}*/

int main() {
    //启动web服务
    unsigned int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    UserController userController;
    userController.exec(server);

    server.run();

    /*auto aa = &Test::say;

    member_args_t<decltype( aa )> bb;

    std::cout << std::tuple_size_v<member_args_t<decltype( aa )>> << std::endl;
    std::tuple_element_t<1, member_args_t<decltype( aa )>>)a = 100;

    std::cout << std::boolalpha;
    std::cout << std::is_same<std::tuple_element_t<1, member_args_t<decltype( aa )>>, double>::value << std::endl;*/

    /*std::cout << "==" << std::endl;

    std::array<int, 5> mm{};
    mm[0] = 100;
    mm[1] = 110;
    mm[2] = 120;
    mm[3] = 130;
    mm[4] = 140;
    a2t(mm, [](int a) {
        std::cout << a << std::endl;
        return a + 100;
    });*/
    /*int a = 50;
    int b = 100;
    char c = 'c';
    auto tup = std::make_tuple(a, b, c, &a);
    std::cout << *std::get<3>(tup) << std::endl;
    std::apply([](int a,int b, char c, const int* d){
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << "d: " << *d << std::endl;
    },tup);*/



}
