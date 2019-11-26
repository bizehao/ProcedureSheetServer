//
// Created by bizehao on 2019/10/31.
//
#include <iostream>
#include <fstream>
#include "../src/utils/reflex.hpp"
#include <type_traits>
#include <chrono>
#include <cassert>
#include <thread>
#include "jwt/jwt.hpp"
#include "../src/base/BaseController.hpp"

int main() {
	using namespace jwt::params;

	jwt::jwt_object obj{ algorithm("hs256"), secret("secret") };
	obj.add_claim("iss", "arun.muralidharan")
		.add_claim("exp", std::chrono::system_clock::now() - std::chrono::seconds{ 1 })
		;

	std::error_code ec;
	auto enc_str = obj.signature(ec);
	assert(!ec);

	auto dec_obj = jwt::decode(enc_str, algorithms({ "hs256" }), ec, secret("secret"), verify(true));
	assert(ec);
	assert(ec.value() == static_cast<int>( jwt::VerificationErrc::TokenExpired ));
	return 0;
}