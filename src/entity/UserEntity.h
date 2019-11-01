//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <string>
#include "ormpp/reflection.hpp"

//用户类型表
struct Occupation {
    int id;
    std::string occupation_name;
};
REFLECTION(Occupation, id, occupation_name)

//struct User {
//    int id; //id
//    std::string username; //用户名
//    std::string password; //密码
//    std::string email; //邮箱地址
//    int type; //用户类型
//    std::string phone; //手机号
//    long latelyDate; //最近一次登录日期
//    std::string ipAddress; //ip地址
//};
//REFLECTION(User, id, username, password, email, type, phone, latelyDate, ipAddress)
