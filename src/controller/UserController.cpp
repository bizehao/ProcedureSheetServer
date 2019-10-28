//
// Created by bizehao on 2019/10/25.
//

#include "UserController.h"

void UserController::exec(cinatra::http_server& server) {
    execNet(*this,
            server,
            SV("/hello2", &UserController::hello2, "a", "b")//,
            //SV("/hello2", &UserController::hello2)
    );
}

void UserController::hello1(cinatra::request& req, cinatra::response& res) {

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
    res.set_status_and_content(cinatra::status_type::ok, "hello1");
}

void UserController::hello2(int a, int b) {
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}
