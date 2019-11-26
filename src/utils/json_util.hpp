#pragma once

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

	enum class http_status {
		success = 200, //正常
		error = 300, //通用错误
		error_token_cm = 301, //token异常
		error_token_bo = 302 //token过期
	};

	//实体对象转成json
	template<http_status ss, typename T>
	std::string conversionJsonOfObj(T&& t, std::string message = "") {
		nlohmann::json json = t;
		json["status"] = static_cast<int>( ss );
		if (!message.empty()) {
			json["message"] = message;
		}
		return json.dump(4);
	}

	//自定义格式内容
	template<http_status ss>
	std::string conversionJsonOfCus(const std::function<void(nlohmann::json&)>& t, std::string message = "") {
		nlohmann::json json;
		json["status"] = static_cast<int>( ss );
		if (!message.empty()) {
			json["message"] = message;
		}
		t(json["data"]);
		return json.dump(4);
	}

	//仅消息
	template<http_status ss>
	std::string conversionJsonOfMsg(std::string message = "") {
		nlohmann::json json;
		json["status"] = static_cast<int>( ss );
		json["message"] = message;
		return json.dump(4);
	}
}