#pragma once

#include "../base/BaseController.hpp"
#include <string>

class OrderController :BaseController {
public:


	OrderController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {};

	~OrderController() {};

	void exec() override;

private:

	std::string submitOrder();
};