#pragma once

#include "../base/BaseController.hpp"

class CommController :BaseController {
public:


	CommController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {};

	~CommController() {};

	void exec() override;

private:
	//��ȡ������֤��
	std::string getEmailCode(std::string& to_user);
};