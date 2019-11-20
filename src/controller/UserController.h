//
// Created by bizehao on 2019/10/25.
// 用户的controller

#pragma once

#include <iostream>
#include <tuple>
#include "../utils/section.h"
#include "../base/BaseController.hpp"

class UserController : BaseController {
public:
	UserController(cinatra::http_server& server, UserMapper& userMapper) : BaseController(server, userMapper) {}

	void exec() override;

private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	登录  </summary>
	///
	/// <remarks>	Bzh, 2019/11/8. </remarks>
	///
	/// <param name="username">	[in,out] 用户名 </param>
	/// <param name="password">	[in,out] 密码 </param>
	///
	/// <returns>	A std::string. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string login(std::string& username, std::string& password);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	注册 </summary>
	///
	/// <remarks>	Bzh, 2019/11/8. </remarks>
	///
	/// <param name="username">	[in,out] 用户名. </param>
	/// <param name="email">   	[in,out] 邮箱地址 </param>
	/// <param name="vercode"> 	[in,out] 验证码 </param>
	/// <param name="password">	[in,out] 密码 </param>
	///
	/// <returns>	A std::string. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string regist(std::string& username, std::string& email, std::string& vercode, std::string& password, int& type);
};
