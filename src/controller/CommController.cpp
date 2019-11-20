#include "CommController.h"
#include "../utils/email/email.h"
#include "../utils/email/email_code_map.h"

void CommController::exec() {

#define CLASS_TYPE CommController
	APPEND_REQUEST(
		SV("/comm/email_code", HttpGet, getEmailCode, "email"),
		SV("/comm/language_list", HttpGet, getLanguageList, "email"),
		SV("/comm/upload_multipart", HttpPost, uploadMultipart, "req", "res", "name")
	)
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
		}, "language type list");
}

void CommController::uploadMultipart(cinatra::request& req, cinatra::response& res, std::string& name) {
	assert(req.get_content_type() == cinatra::content_type::multipart);
	std::cout << "name is " << name << std::endl;
	auto& files = req.get_upload_files();
	for (auto& file : files) {
		std::cout << file.get_file_path() << " " << file.get_file_size() << std::endl;
	}
	res.set_status_and_content(cinatra::status_type::ok, "multipart finished");
}
