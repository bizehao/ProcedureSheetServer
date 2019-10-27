// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"
//#include "cinatra.hpp"
#include "utils/reflex.hpp"
#include <functional>
#include <iostream>

struct Test {
public:
	Test() {}
	void say(int a, double b) {
		std::cout << a << b << std::endl;
	}
};

int main() {
	//启动web服务
	unsigned int max_thread_num = std::thread::hardware_concurrency();
	cinatra::http_server server(max_thread_num);
	server.listen("0.0.0.0", "8080");
	UserController userController;
	userController.exec(server);
	server.run();

	/*Test test;

	auto aa = &Test::say;

	member_args_t<decltype( aa )> bb;

	std::cout << std::tuple_size_v<member_args_t<decltype( aa )>> << std::endl;

	std::cout << std::boolalpha;
	std::cout << std::is_same<std::tuple_element_t<1, member_args_t<decltype( aa )>>, double>::value << std::endl;*/
}
