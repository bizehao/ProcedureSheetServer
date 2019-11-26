#pragma once

#include "../base/BaseController.hpp"

#define CLASS_TYPE TestController

class TestController : BaseController {
public:
	TestController(cinatra::http_server& server_, UserMapper& userMapper_) : BaseController(server_), userMapper(userMapper_) {};

	void exec() override {

		APPEND_REQUEST(
			SV("/test/test", HttpGet, test, a, b)
		)
	};

private:
	UserMapper& userMapper;

	std::string test(std::string& a, std::string& b);
};