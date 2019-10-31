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
#include "mapper/UserMapper.h"

int main() {
#ifdef _WIN32
	system("chcp 65001");
#endif
    //连接mysql
    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect("127.0.0.1", "root", "bzh960912", "procedure-sheet");

    //启动web服务
	unsigned int max_thread_num = std::thread::hardware_concurrency();
	cinatra::http_server server(max_thread_num);
	server.listen("0.0.0.0", "8080");
    UserMapper userMapper(mysql);
	UserController userController(server,userMapper);
	userController.exec();
	server.run();
}
