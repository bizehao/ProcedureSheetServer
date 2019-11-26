#pragma once

#include "../base/BaseController.hpp"
#include <string>

#define CLASS_TYPE OrderController

class OrderController :BaseController {
public:

	OrderController(cinatra::http_server& server_, UserMapper& userMapper_) : BaseController(server_), userMapper(userMapper_) {};

	~OrderController() {};

	void exec() override {
		APPEND_REQUEST(
			SV("/order/submit_order", HttpPost, submitOrder, title, demand, budget, languageid, userid, req)
		);
	};

private:

	UserMapper& userMapper;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit order./ </summary>
	///
	/// <remarks>	Bzh, 2019/11/21. </remarks>
	///
	/// <param name="title"> ��������	 	[in,out] The title. </param>
	/// <param name="demand"> ��������	  	[in,out] The demand. </param>
	/// <param name="budget"> ����Ԥ��	 	[in,out] The bud get. </param>
	/// <param name="languageid"> �����������     	[in,out] The languageid. </param>
	/// <param name="userid"> �ύ�������û�id 	 	[in,out] The userid. </param>
	/// <param name="req">		 	[in,out] The request. </param>
	///
	/// <returns>	A std::string. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string submitOrder(std::string& title, std::string& demand, double& budget,
		int& languageid, int& userid, cinatra::request& req);
};