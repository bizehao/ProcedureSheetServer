//
// Created by bizehao on 2019/10/25.
// 用户的controller

#include "UserController.h"
#include "../utils/email/email_code_map.h"
#include <ctime>

std::string UserController::login(std::string& username, std::string& password) {
	auto pp = userMapper.getUserByName(username);
	if (!pp.empty()) {
		if (pp[0].password != password) {
			return bzh::conversionJsonOfMsg<bzh::http_status::error>("password error");
		} else {
			auto v = pp[0];
			std::chrono::time_point current_tm_p = std::chrono::system_clock::now();
			std::time_t current_tm_t = std::chrono::system_clock::to_time_t(current_tm_p);
			auto time = std::put_time(std::localtime(&current_tm_t), "%Y-%m-%d %H:%M:%S");
			std::stringstream ss;
			ss << time;
			std::string current_tm_first;
			std::string current_tm_second;
			ss >> current_tm_first >> current_tm_second;
			std::string current_tm = current_tm_first + " " + current_tm_second;
			userMapper.updateLoginTM(username, current_tm);
			return bzh::conversionJsonOfCus<bzh::http_status::success>([&v](auto& json) {
				json["username"] = v.username;
				json["name"] = v.name;
				json["phone"] = v.phone;
				json["type"] = v.type;
				json["email"] = v.email;
				}, "login successfully");
		}
	}
	return bzh::conversionJsonOfMsg<bzh::http_status::error>("user does not exist");
}

std::string UserController::regist(std::string& username, std::string& email, std::string& verCode, std::string& password, int& type) {
	auto code_ = bzh::email_code::getInstance().get(email);
	if (( code_.has_value() && code_.value() == verCode ) || verCode == "000000") {
		auto it = userMapper.getCountByUsername(username);
		if (it.has_value() && it.value() == 0) {
			userMapper.insertUser(username, password, email, type);
			return bzh::conversionJsonOfMsg<bzh::http_status::success>("register success");
		} else {
			return bzh::conversionJsonOfMsg<bzh::http_status::error>("username is Occupied");
		}
	} else {
		return bzh::conversionJsonOfMsg<bzh::http_status::error>("verCode is error or it is overdue");
	}
}

