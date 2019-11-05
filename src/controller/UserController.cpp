//
// Created by bizehao on 2019/10/25.
// 用户的controller

#include "UserController.h"

void UserController::exec() {
    execNet(*this,
            server,
            SV("/user/login", HttpPost{}, &UserController::login, "username", "password")
    );
};

/**
 * 登录
 * 返回用户的id,
 */
std::string UserController::login(std::string& username, std::string& password) {
    auto pp = userMapper.getUserByName();
    if (!pp.empty()) {
        if (pp[0].password != password) {
            return bzh::conversionJsonOfMsg<bzh::status::error>("password error");
        } else {
            auto v = pp[0];
            return bzh::conversionJsonOfCus<bzh::status::success>([&v](auto& json) {
                json["username"] = v.username;
                json["name"] = v.name;
                json["phone"] = v.phone;
                json["type"] = v.type;
                json["email"] = v.email;
            }, "login successfully");
        }
    }
    return bzh::conversionJsonOfMsg<bzh::status::error>("user does not exist");
}

//注册
std::string UserController::regist() {
    std::string xx = "asxx2";
    return "as";
}

