//
// Created by bizehao on 2019/10/31.
//

#include "UserMapper.h"
#include "../utils/currency_sql.hpp"

std::vector<bzh::User> UserMapper::getUserByName(std::string& username) {
	return bzh::customizeQuery<bzh::User>(mysql, "select username, password, name, email, type, phone, lately_date from users where username = ?", username);
}

bool UserMapper::updateLoginTM(std::string& username, std::string& datetime) {
	return bzh::customizeCUD(mysql, "UPDATE users SET lately_date = ? where username = ?", datetime, username);
}

std::optional<int> UserMapper::getCountByEmail(std::string& email) {
	return bzh::customizeQueryOfSingle<int>(mysql, "SELECT count(*) FROM users where email = ?", email);
}

std::optional<int> UserMapper::getCountByUsername(std::string& username) {
	return bzh::customizeQueryOfSingle<int>(mysql, "SELECT count(*) FROM users where username = ?", username);
}

bool UserMapper::insertUser(std::string& username, std::string& password, std::string& email, int& type) {
	return bzh::customizeCUD(mysql, "INSERT INTO users ( username, password, name, email, type ) VALUES (?, ?, ?, ?, ?)",
		username, password, username, email, std::to_string(type));
}

std::vector<bzh::LanguageType> UserMapper::getLanguageList() {
	return bzh::customizeQuery<bzh::LanguageType>(mysql, "SELECT id, language_name FROM language_type");
}
