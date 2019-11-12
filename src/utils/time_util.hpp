#include <chrono>
#include <string>

std::string time_to_string(std::tm*& timeinfo) {
	/*std::string datetime = std::to_string(timeinfo->tm_year + 1900) + "-" +
		std::to_string(timeinfo->tm_mon + 1) + "-" +
		std::to_string(timeinfo->tm_mday) + " " +
		std::to_string(timeinfo->tm_hour) + ":" +
		std::to_string(timeinfo->tm_min) + ":" +
		std::to_string(timeinfo->tm_sec);*/
	std::string datetime = std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
	return std::move(datetime);
}