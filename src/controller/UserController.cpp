//
// Created by bizehao on 2019/10/25.
//

#include "UserController.h"

void UserController::exec(cinatra::http_server &server) {
    execNet(*this,
         server,
         SV("/hello1", &UserController::hello1),
         SV("/hello2", &UserController::hello2)
    );
}

void UserController::hello1(cinatra::request &req, cinatra::response &res) {
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
    }
})";
    res.set_status_and_content(cinatra::status_type::ok, std::move(mm));
}

void UserController::hello2(cinatra::request &req, cinatra::response &res) {
    int x = 100;
    constexpr auto mm = R"({
    "animals":{
        "dog":[
            {
                "name":"Rufus",
                "age":15
            },
            {
                "name":"Marty",
                "age":"hello2"
            }
        ]
    }
})";
    res.set_status_and_content(cinatra::status_type::ok, std::move(mm));
}
