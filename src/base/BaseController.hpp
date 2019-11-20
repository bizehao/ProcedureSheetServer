//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <cinatra/http_server.hpp>
#include "../mapper/UserMapper.h"
#include "../utils/currency_net.hpp"
#include <functional>

//定义那个类
#define CLASS_TYPE

//添加
#define APPEND_REQUEST(...) baseExecNet(static_cast<CLASS_TYPE>(*this), ##__VA_ARGS__);

//第一个请求头  第二个请求的方法地址 剩余的为参数字段名
#define SV(REQ_ADDRESS, REQ_TYPE, REQ_METHOD, ...) std::make_tuple(REQ_ADDRESS, REQ_TYPE{}, &CLASS_TYPE::REQ_METHOD, ##__VA_ARGS__)

struct HttpGet {
	static constexpr auto reqMethod = cinatra::GET;
};

struct HttpPost {
	static constexpr auto reqMethod = cinatra::POST;
};

namespace bzh {

	// class
	template<typename T>
	std::enable_if_t<iguana::is_reflection_v<T>, void> to_json(nlohmann::json& j, const T& p) {
		j = nlohmann::json{};
		iguana::for_each(p, [&j, &p](auto item, auto i) {
			constexpr auto Idx = decltype( i )::value;
			std::string_view fieldName = iguana::get_name<T>(Idx);
			j[fieldName.data()] = p.*item;
			});
	}

	//vector<class>
	template<typename T>
	std::enable_if_t<iguana::is_reflection_v<T>, void> to_json(nlohmann::json& j, const std::vector<T>& p) {
		j = nlohmann::json{};
		for (auto& it : p) {
			nlohmann::json tmpJson;
			iguana::for_each(it, [&j, &it, &tmpJson](auto item, auto i) {
				constexpr auto Idx = decltype( i )::value;
				std::string_view fieldName = iguana::get_name<T>(Idx);
				tmpJson[fieldName.data()] = it.*item;
				});
			j.push_back(tmpJson);
		}
	}

	enum class status {
		success = 200,
		error = 300
	};

	//实体对象转成json
	template<status ss, typename T>
	std::string conversionJsonOfObj(T&& t, std::string message = "") {
		nlohmann::json json = t;
		json["status"] = static_cast<int>( ss );
		if (!message.empty()) {
			json["message"] = message;
		}
		return std::move(json.dump(4));
	}

	//自定义格式内容
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

	//仅消息
	template<status ss>
	std::string conversionJsonOfMsg(std::string message = "") {
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

	template<typename OBJ, typename... T>
	void baseExecNet(OBJ&& obj, T... t) {
		execNet(obj, server, t...);
	}

	cinatra::http_server& server;
	UserMapper& userMapper;
};
