#pragma once

#include "../base/BaseController.hpp"

#define CLASS_TYPE CommController

class CommController :BaseController {
public:


	CommController(cinatra::http_server& server_, UserMapper& userMapper_) : BaseController(server_), userMapper(userMapper_) {};

	~CommController() {};
	
	 
	void exec() override {
		 
		APPEND_REQUEST(
			SV("/comm/email_code", HttpGet, getEmailCode, email),
			SV("/comm/language_list", HttpGet, getLanguageList),
			SV("/comm/upload_multipart", HttpPost, uploadMultipart, req, res, name)
		)
	};

private:

	UserMapper& userMapper;

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

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	获取语言类型列表   </summary>
	///
	/// <remarks>	Bzh, 2019/11/18. </remarks>
	///
	/// <returns>	The language list. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string getLanguageList();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	上传图片  </summary>
	///
	/// <remarks>	Bzh, 2019/11/20. </remarks>
	///
	/// <param name="req">	[in,out] The request. </param>
	/// <param name="res">	[in,out] The resource. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void uploadMultipart(cinatra::request& req, cinatra::response& res, std::string& name);
};