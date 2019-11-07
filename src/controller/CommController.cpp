#include "CommController.h"
#include "../utils/email/email.h"

void CommController::exec() {
	execNet(*this,
		server,
		SV("/comm/email_code", HttpGet{}, &CommController::getEmailCode, "to_user")
	);
}

std::string CommController::getEmailCode(std::string& to_user) {
	std::string xx = bzh::seedEmail(to_user);
	return xx;
}
