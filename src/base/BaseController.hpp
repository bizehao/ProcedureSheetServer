//
// Created by bizehao on 2019/10/31.
//

#pragma once

class BaseController{
public:
private:
    cinatra::http_server& server;
    UserMapper& userMapper;
};
