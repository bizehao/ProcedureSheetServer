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
        std::string name;
        std::string email;
        int type;
        std::string phone;
        std::string lately_date;
        std::string ip_address;
    };

    REFLECTION(Occupation, id, occupation_name)

    REFLECTION(User, id, username, password, name, email, type, phone, lately_date, ip_address)
}
