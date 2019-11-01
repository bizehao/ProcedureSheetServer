//
// Created by bizehao on 2019/10/25.
//

#pragma once

#include "cinatra.hpp"

using namespace cinatra;

//»’÷æ«–√Ê
struct log_t {
	bool before(request& req, response& res) {
		std::cout << "before log" << std::endl;
		return true;
	}

	bool after(request& req, response& res) {
		std::cout << "after log" << std::endl;
		return true;
	}
};
