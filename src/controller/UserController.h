//
// Created by bizehao on 2019/10/25.
// 用户的controller

#ifndef PROCEDURESHEETSERVER_USERCONTROLLER_H
#define PROCEDURESHEETSERVER_USERCONTROLLER_H
#include "cinatra.hpp"


class UserController {
public:
    void exec(cinatra::http_server &server);
private:
    void hello1(cinatra::request& req, cinatra::response& res);
    void hello2(cinatra::request& req, cinatra::response& res);
};


#endif //PROCEDURESHEETSERVER_USERCONTROLLER_H
