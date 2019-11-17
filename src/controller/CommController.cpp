#include "CommController.h"
#include "../utils/email/email.h"
#include "../utils/email/email_code_map.h"

void CommController::exec() {
	execNet(*this,
		server,
		SV("/comm/email_code", HttpGet{}, &CommController::getEmailCode, "email"),
		SV("/comm/language_list", HttpGet{}, &CommController::getLanguageList)
	);
}

std::string CommController::getEmailCode(std::string& email) {
	auto vv = userMapper.getCountByEmail(email);
	if (vv.has_value() && vv.value() == 0) {
		std::string code = bzh::seedEmail(email);
		bzh::email_code::getInstance().put(email, bzh::email_code::email_code_model{ std::chrono::system_clock::now(),std::move(code) });
		return bzh::conversionJsonOfMsg<bzh::status::success>("email seed success");
	} else {
		return bzh::conversionJsonOfMsg<bzh::status::error>("email is occupied");
	}
}

std::string CommController::getLanguageList() {
	auto language_list = userMapper.getLanguageList();
	return bzh::conversionJsonOfCus<bzh::status::success>([&language_list](nlohmann::json& json) {
		json = language_list;
		},"language type list");
}
