#include "ProcedureSheetServer.h"

class xx {
public:
	xx() {
		std::cout << "gouzao" << std::endl;
	}
	~xx() {
		std::cout << "xigou" << std::endl;
	}
};

int main() {
	//设置日志格式
	spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [thread %t] %v");
#ifdef _WIN32
	system("chcp 65001");
	std::ifstream read("F:\\source\\repos\\ProcedureSheetServer\\resources\\application.json");
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

	//init email
	MyMail::init(in["email"]["host"].get<std::string>(), in["email"]["myemail"].get<std::string>(), in["email"]["password"].get<std::string>());

	//start web server
	unsigned int max_thread_num = std::thread::hardware_concurrency();
	cinatra::http_server server(max_thread_num);
	//公共资源api  http://xxx:xxx/resources/imgs/xxx.xxx
	server.set_public_root_directory("resources/imgs", in["resources"]["public_root_directory"].get<std::string>());
	server.set_static_dir("/");//图片下载的资源目录
	server.enable_http_cache(false);//set global cache
	server.set_res_cache_max_age(86400);
	server.set_cache_max_age(5);
	server.listen(in["address"].get<std::string>(), in["port"].get<std::string>());
	UserMapper userMapper(mysql);
	UserController(server, userMapper).exec();
	CommController(server, userMapper).exec();
	OrderController(server, userMapper).exec();
	TestController(server, userMapper).exec();
	//start web socket
	MyWebSocket myWebSocket;
	server.set_http_handler<cinatra::GET, cinatra::POST>("/ws", [&myWebSocket](cinatra::request& req, cinatra::response& res) {
		assert(req.get_content_type() == cinatra::content_type::websocket);

		req.on(cinatra::ws_open, [&myWebSocket](cinatra::request& req) {
			spdlog::info("websocket start");
			myWebSocket.onOpen(req);
			});

		req.on(cinatra::ws_message, [&myWebSocket](cinatra::request& req) {
			spdlog::info("websocket message");
			auto part_data = req.get_part_data();
			//echo
			std::string str = std::string(part_data.data(), part_data.length());
			req.get_conn()->send_ws_string(std::move(str));
			std::cout << part_data.data() << std::endl;
			myWebSocket.onMessage(req);
			});

		req.on(cinatra::ws_close, [&myWebSocket](cinatra::request& req) {
			spdlog::info("websocket close");
			myWebSocket.onClose(req);
			});

		req.on(cinatra::ws_error, [&myWebSocket](cinatra::request& req) {
			spdlog::info("websocket error");
			myWebSocket.onError(req);
			});
		});

	server.run();
	return EXIT_SUCCESS;
}