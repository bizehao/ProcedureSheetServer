//
// Created by bizehao on 2019/10/25.
//

#include "UserController.h"

void UserController::exec() {
	execNet(*this,
		server,
		SV("/hello2", &UserController::login, "name", "password")
	);
}

std::string UserController::hello1(cinatra::request& req, cinatra::response& res) {

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

//http://localhost:8080/hello2?a=58
std::string UserController::login(int& name, int& password) {
	std::cout << "½øÈëhello2: " << std::endl;
    //auto pp = userMapper.getUserByName();
	return "ºÃ°Éhello2";
}
