// ProcedureSheetServer.cpp: 定义应用程序的入口点。
//

#include "ProcedureSheetServer.h"

int main() {
#ifdef _WIN32
	std::ifstream read("C:\\Users\\24221\\source\\repos\\ProcedureSheetServer\\resources\\application.json");
#else
	std::ifstream read("../resources/application.json");
#endif
    
    nlohmann::json in = nlohmann::json::parse(read);

    //连接mysql
    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect(in["address"].get<std::string>().data(),
                  in["database"]["user"].get<std::string>().data(),
                  in["database"]["password"].get<std::string>().data(),
                  in["database"]["db"].get<std::string>().data()
                  );

    //启动web服务
    unsigned int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    //server.listen("127.0.0.1", "8080");
    server.listen(in["address"].get<std::string>(), in["port"].get<std::string>());
    UserMapper userMapper(mysql);
    UserController userController(server,userMapper);
    userController.exec();
    server.run();
}
