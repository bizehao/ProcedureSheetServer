//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <string>
#include "ormpp/reflection.hpp"

namespace bzh {
	struct Occupation {
		int id;
		std::string occupation_name;
	};


	struct User {
		int id;
		std::string username;
		std::string password;
		std::string email;
		int type;
		std::string phone;
		std::string lately_date;
		std::string ip_address;
	};

	//登录成功的用户信息
	struct JSONOfUser {
		std::string name;
		std::string data;
	};

	REFLECTION(Occupation, id, occupation_name)
	REFLECTION(JSONOfUser, name, data)
	REFLECTION(User, id, username, password, email, type, phone, lately_date, ip_address)
}
