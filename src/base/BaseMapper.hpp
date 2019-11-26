//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"

class BaseMapper{
public:
    BaseMapper(ormpp::dbng<ormpp::mysql>& mysql_):mysql(mysql_){}
protected:
    ormpp::dbng<ormpp::mysql>& mysql;
};