//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <cinatra/http_server.hpp>
#include "../mapper/UserMapper.h"

class BaseController{
public:
    BaseController(cinatra::http_server& server, UserMapper& userMapper):server(server),userMapper(userMapper){}

    virtual void exec() = 0;

    virtual ~BaseController()= default;

protected:
    cinatra::http_server& server;
    UserMapper& userMapper;
};
