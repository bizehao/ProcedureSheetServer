//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <cinatra/http_server.hpp>
#include "../mapper/UserMapper.h"
#include "../utils/currency_net.hpp"
#include <functional>

//第一个请求头  第二个请求的方法地址 剩余的为参数字段名
#define SV(...) std::make_tuple(__VA_ARGS__)

struct HttpGet {
    static constexpr auto reqMethod = cinatra::GET;
};

struct HttpPost {
    static constexpr auto reqMethod = cinatra::POST;
};

namespace bzh {

    template<typename T>
    void to_json(nlohmann::json& j, const T& p) {
        j = nlohmann::json{};
        if constexpr (iguana::is_reflection_v<T>) {
            iguana::for_each(p, [&j, &p](auto item, auto i) {
                constexpr auto Idx = decltype( i )::value;
                std::string_view fieldName = iguana::get_name<T>(Idx);
                j["data"][fieldName.data()] = p.*item;
            });
        } else {
            std::cout << "it is not reflection" << std::endl;
        }
    }

    enum class status {
        success = 200,
        error = 300
    };

    template<status ss, typename T>
    std::string conversionJsonOfObj(T&& t, std::string message = "") {
        nlohmann::json json = t;
        json["status"] = static_cast<int>( ss );
        if (!message.empty()) {
            json["message"] = message;
        }
        return std::move(json.dump(4));
    }

    template<status ss>
    std::string conversionJsonOfCus(const std::function<void(nlohmann::json&)>& t, std::string message = "") {
        nlohmann::json json;
        json["status"] = static_cast<int>( ss );
        if (!message.empty()) {
            json["message"] = message;
        }
        t(json["data"]);
        return std::move(json.dump(4));
    }

    template<status ss>
    std::string conversionJsonOfMsg(std::string message) {
        nlohmann::json json;
        json["status"] = static_cast<int>( ss );
        json["message"] = message;
        return std::move(json.dump(4));
    }
}


class BaseController {
public:
    BaseController(cinatra::http_server& server, UserMapper& userMapper) : server(server), userMapper(userMapper) {}

    virtual void exec() = 0;

    virtual ~BaseController() = default;

protected:
    cinatra::http_server& server;
    UserMapper& userMapper;
};
