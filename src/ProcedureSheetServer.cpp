// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"
#include "cinatra.hpp"
#include "utils/reflex.hpp"
#include <functional>
#include <iostream>
#include <tuple>
#include <array>
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "utils/currency_sql.hpp"

struct Student {
    int id;
    std::string name;
	int age;
};
REFLECTION(Student, id, name, age)

int main() {
#ifdef _WIN32
	system("chcp 65001");
#endif
    //连接mysql
    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect("127.0.0.1", "root", "bzh960912", "testcpp");

	auto pp = bzh::customizeQuery<Student>(mysql, "select * from student");
	for (auto& item : pp) {
		std::cout << "id" << item.id << "名字" << item.name << "年龄" << item.age << std::endl;
	}

    //启动web服务
	unsigned int max_thread_num = std::thread::hardware_concurrency();
	cinatra::http_server server(max_thread_num);
	server.listen("0.0.0.0", "8080");
	UserController userController;
	userController.exec(server);
	server.run();
}
