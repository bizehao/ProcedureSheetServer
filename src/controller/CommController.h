#pragma once

#include "../base/BaseController.hpp"

class CommController :BaseController {
public:


	CommController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {};

	~CommController() {};

	void exec() override;

private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	获取邮箱验证码. </summary>
	///
	/// <remarks>	Bzh, 2019/11/8. </remarks>
	///
	/// <param name="to_user">	[in,out] 邮箱地址 </param>
	///
	/// <returns>	The email code. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string getEmailCode(std::string& email);

	std::string getLanguageList();
};