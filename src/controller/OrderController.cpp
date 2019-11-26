#include "OrderController.h"
#include <chrono>

std::string OrderController::submitOrder(std::string& title, std::string& demand, double& budget, int& languageid, int& userid, cinatra::request& req) {
	/*auto filename = req.get_filename_from_path();
	std::cout << "show " << filename << std::endl;
	auto& files = req.get_upload_files();
	for (auto& file : files) {
		std::cout << file.get_file_path() << " " << file.get_file_size() << std::endl;
	}*/
	std::cout << "<<<<<<<<<<>>>>>>>>>" << std::endl;
	return bzh::conversionJsonOfMsg<bzh::http_status::success>();
}
