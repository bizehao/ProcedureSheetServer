//
// Created by bizehao on 2019/10/25.
//

#pragma once

#include "cinatra.hpp"
#include "spdlog/spdlog.h"
#include <chrono>
#include <thread>
#include "jwt/jwt.hpp"
#include "json_util.hpp"

//日志切面
struct log_t {

	bool before(cinatra::request& req, cinatra::response& res) {

		begin_time = std::chrono::steady_clock::now();
		auto map = req.get_multipart_form_map();
		spdlog::info("request http: {}", req.get_url());
		spdlog::info("args: ");
		for (const auto& begin : map) {
			spdlog::info("    {:<15}{}", begin.first, begin.second);
		}
		return true;
	}

	bool after(cinatra::request& req, cinatra::response& res) {
		end_time = std::chrono::steady_clock::now();
		std::chrono::microseconds timeInterval = std::chrono::duration_cast<std::chrono::microseconds>( end_time - begin_time );
		spdlog::info("result: \n{}", res.get_content());
		spdlog::info("time consuming: {}μs", timeInterval.count());
		return true;
	}

private:
	std::chrono::steady_clock::time_point begin_time;
	std::chrono::steady_clock::time_point end_time;
};

struct jwt_t {

	static constexpr auto key = "secret"; //Secret to use for the algorithm

	bool before(cinatra::request& req, cinatra::response& res) {
		if (req.get_url() != "/user/login" && req.get_url() != "/user/register") { //不是登陆注册接口 鉴权
			std::cout << "yan zheng token" << std::endl;
			using namespace jwt::params;
			auto enc_str = req.get_header_value("jwt");
			std::string mm(enc_str);
			try {
				//Decode
				jwt::jwt_object dec_obj = jwt::decode(mm, algorithms({ "hs256" }), secret(key), verify(true));
				//token有效
				std::cout << dec_obj.header() << std::endl;
				std::cout << dec_obj.payload() << std::endl;
				std::cout << "token success" << std::endl;
				return true;
			}  catch (const jwt::TokenExpiredError& exc) {
				//token到期
				std::cout << "token1 exception: " << exc.what() << std::endl;
				res.set_status_and_content(cinatra::status_type::ok, 
					bzh::conversionJsonOfMsg<bzh::http_status::error_token_bo>("token be overdue")
				);
				return false;
			} catch (const std::exception & exc) {
				//token错误
				std::cout << "token2 exception: " << exc.what() << std::endl;
				res.set_status_and_content(cinatra::status_type::ok, 
					bzh::conversionJsonOfMsg<bzh::http_status::error_token_cm>("token be bad")
				);
				return false;
			}
		}
		return true;
	}

	bool after(cinatra::request& req, cinatra::response& res) {
		if (req.get_url() == "/user/login") { //是登陆接口 发放token
			nlohmann::json json = nlohmann::json::parse(res.get_content());

			if (json["status"].get<int>() == static_cast<int>(bzh::http_status::success)) { //登录成功
				using namespace jwt::params;
				//生成token
				//Create JWT object
				jwt::jwt_object obj{ algorithm("HS256"), payload({{"user", "ordinary"}}), secret(key) };
				obj.add_claim("iss", "bzh"). //签发者
					add_claim("sub", "Pass check"). //主题
					add_claim("aud", "ordinary"). //接收者
					add_claim("iat", std::chrono::system_clock::now()). //签发时间
					add_claim("exp", std::chrono::system_clock::now() + std::chrono::hours(60)); //到期时间

				//Get the encoded string/assertion
				auto enc_str = obj.signature();
				//std::move(enc_str)
				res.add_header("jwt", std::move(enc_str));
			}
		}

		return true;
	}
};
