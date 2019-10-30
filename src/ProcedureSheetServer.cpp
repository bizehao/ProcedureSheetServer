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

struct occupation {
    int id;
    std::string name;
};
REFLECTION(occupation, id, name)

int main() {



    //连接mysql
    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect("127.0.0.1", "root", "bzh960912", "procedure-sheet");
    auto resule = mysql.query<occupation>();
    std::cout << "输出结果" << std::endl;
    //std::cout << std::get<0>(resule[0]) << "  " << std::get<1>(resule[0]) << std::endl;

    //启动web服务
    /*unsigned int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    UserController userController;
    userController.exec(server);
    server.run();*/
}
