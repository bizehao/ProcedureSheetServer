//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <string>
#include "ormpp/reflection.hpp"

//�û����ͱ�
struct Occupation {
    int id;
    std::string occupation_name;
};
REFLECTION(Occupation, id, occupation_name)

//struct User {
//    int id; //id
//    std::string username; //�û���
//    std::string password; //����
//    std::string email; //�����ַ
//    int type; //�û�����
//    std::string phone; //�ֻ���
//    long latelyDate; //���һ�ε�¼����
//    std::string ipAddress; //ip��ַ
//};
//REFLECTION(User, id, username, password, email, type, phone, latelyDate, ipAddress)
