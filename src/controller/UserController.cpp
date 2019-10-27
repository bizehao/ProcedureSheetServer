//
// Created by bizehao on 2019/10/25.
//

#include "UserController.h"

void UserController::exec(cinatra::http_server& server) {
	execNet(*this,
		server,
		SV("/hello1", &UserController::hello1),
		SV("/hello2", &UserController::hello2)
	);
}

void UserController::hello1(cinatra::request& req, cinatra::response& res) {
	int x = 100;
	std::string mm = R"({
    "animals":{
        "dog":[
            {
                "name":"Rufus",
                "age":15
            },
            {
                "name":"Marty",
                "age":null
            }
        ]
    }})";
	res.set_status_and_content(cinatra::status_type::ok, std::move(mm));
}

void UserController::hello2(cinatra::request& req, cinatra::response& res) {

	auto a = req.get_query_value("a");
	auto b = req.get_query_value("b");

	auto x = req.get_query_value(0);

	std::cout << "a: " << a << std::endl;

	std::cout << "b: " << b << std::endl;

	std::cout << "x: " << x << std::endl;

	res.set_status_and_content(cinatra::status_type::ok, "test success");
}
