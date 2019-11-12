//
// Created by bizehao on 2019/10/31.
//
#include "cinatra.hpp"
#include <iostream>
#include <stack>

using namespace std;

int main() {
	cinatra::http_server _server(1);
	_server.listen("0.0.0.0", "8080");
	_server.set_http_handler<cinatra::GET>("/ws", [](cinatra::request& req, cinatra::response& res) {
		res.add_header("Cache-control", "no-store");
		res.add_header("Access-Control-Allow-Origin", "*");
		res.add_header("Access-Control-Allow-Headers", "X-Requested-With,Content-Type,Accept");
		res.add_header("Access-Control-Allow-Methods", "GET");
		std::cout << "on request" << std::endl;
		if (req.get_content_type() != cinatra::content_type::websocket) {
			res.set_status_and_content(cinatra::status_type::ok, "the url only can access by websocket protocol");
		} else {
			req.on(cinatra::ws_open, [](cinatra::request& req) {
				std::cout << "websocket start" << std::endl;
				});
			req.on(cinatra::ws_message, [](cinatra::request& req) {
				auto _data = req.get_part_data();
				std::cout << "websocket recv: " << _data << std::endl;
				});
			req.on(cinatra::ws_close, [](cinatra::request& req) {
				std::cout << "websocket close" << std::endl;
				});
			req.on(cinatra::ws_error, [](cinatra::request& req) {
				std::cout << "websocket error" << std::endl;
				});
		}
		});
	_server.run();
	std::cout << "exit." << std::endl;
	std::getchar();
}