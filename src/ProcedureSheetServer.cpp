// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"
#include "cinatra.hpp"


int main() {
    //启动web服务
    unsigned int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen("0.0.0.0", "8080");
    UserController userController;
    userController.exec(server);
    server.run();
}
