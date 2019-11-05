// ProcedureSheetServer.cpp:
//

#include "ProcedureSheetServer.h"

int main() {
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [thread %t] %v");
#ifdef _WIN32
    //system("chcp 65001");
    std::ifstream read("C:\\Users\\24221\\source\\repos\\ProcedureSheetServer\\resources\\application.json");
#else
    std::ifstream read("../resources/application.json");
#endif

    nlohmann::json in = nlohmann::json::parse(read);

    //connect mysql
    ormpp::dbng<ormpp::mysql> mysql;
    mysql.connect(in["database"]["address"].get<std::string>().data(),
                  in["database"]["user"].get<std::string>().data(),
                  in["database"]["password"].get<std::string>().data(),
                  in["database"]["db"].get<std::string>().data()
    );

    //start web server
    unsigned int max_thread_num = std::thread::hardware_concurrency();
    cinatra::http_server server(max_thread_num);
    server.listen(in["address"].get<std::string>(), in["port"].get<std::string>());
    UserMapper userMapper(mysql);
    UserController userController(server, userMapper);
    userController.exec();
    //start web socket
    server.set_http_handler<cinatra::GET, cinatra::POST>("/ws", [](cinatra::request& req, cinatra::response& res) {
        assert(req.get_content_type() == cinatra::content_type::websocket);

        req.on(cinatra::ws_open, [](cinatra::request& req) {
            spdlog::info("websocket start");
        });

        req.on(cinatra::ws_message, [](cinatra::request& req) {
            spdlog::info("websocket message");
            auto part_data = req.get_part_data();
            //echo
            std::string str = std::string(part_data.data(), part_data.length());
            req.get_conn()->send_ws_string(std::move(str));
            std::cout << part_data.data() << std::endl;
        });

        req.on(cinatra::ws_close, [](cinatra::request& req) {
            spdlog::info("websocket close");
        });

        req.on(cinatra::ws_error, [](cinatra::request& req) {
            spdlog::info("websocket error");
        });
    });
    server.run();
    return EXIT_SUCCESS;
}






















