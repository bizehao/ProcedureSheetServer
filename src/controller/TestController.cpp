#include "TestController.h"

std::string TestController::test(std::string& a,std::string& b) {
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	return bzh::conversionJsonOfMsg<bzh::http_status::error>("password error");
}
