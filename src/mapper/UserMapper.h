//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <vector>
#include "../entity/UserEntity.h"
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "../base/BaseMapper.hpp"
#include <optional>

//==sql==
class UserMapper : BaseMapper {
public:
	explicit UserMapper(ormpp::dbng<ormpp::mysql>& mysql) : BaseMapper(mysql) {}

	//��ȡ�û�ͨ������
	std::vector<bzh::User> getUserByName(std::string& username);

	//�޸��û��ĵ�¼ʱ��
	bool updateLoginTM(std::string& username, std::string& datetime);

	//��ȡemail�Ƿ����û�����ʹ��
	std::optional<int> getCountByEmail(std::string& email);

	//��ȡusername�Ƿ����û�����ʹ��
	std::optional<int> getCountByUsername(std::string& email);

	//����û�
	bool insertUser(std::string& username, std::string& password, std::string& email, int& type);

	//��ȡ�����б�
	std::vector<bzh::LanguageType> getLanguageList();
};


