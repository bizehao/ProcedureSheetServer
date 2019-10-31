//
// Created by bizehao on 2019/10/25.
//

#include "UserController.h"

void UserController::exec() {
	execNet(*this,
		server,
		SV("/hello2", &UserController::hello2)
	);
}

std::string UserController::hello1(cinatra::request& req, cinatra::response& res) {

	auto a = req.get_query_value("a");
	auto b = req.get_aspect_data();
	auto c = req.get_form_url_map();
	std::cout << "a: " << a << std::endl;
	//queries
	/*int x = 100;
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
	}})";*/
	return "11";
}

//int& a, int& b,
std::string UserController::hello2() {
	std::cout << "进入hello2" << std::endl;
    auto pp = userMapper.getOccupations();
    for (auto& item : pp) {
        std::cout << "id: " << item.id << "类型: " << item.occupation_name << std::endl;
    }
	return "好吧hello2";
}
