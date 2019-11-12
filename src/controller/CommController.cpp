#include "CommController.h"
#include "../utils/email/email.h"
#include "../utils/email/email_code_map.h"

void CommController::exec() {
	execNet(*this,
		server,
		SV("/comm/email_code", HttpGet{}, &CommController::getEmailCode, "email")
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
