//
// Created by bizehao on 2019/10/31.
//
#include <iostream>
#include <fstream>
#include <io.h>


int main() {
	std::ifstream src_path("G:\\�ĵ�\\api");
	if (src_path.is_open()) {
		std::cout << "����" << std::endl;
	} else {
		std::cout << "������" << std::endl;
	}
	std::string prefix = "G:/test/";
	if (_access(prefix.c_str(), 0) == -1) {//����ļ��в�����
		��_mkdir(prefix.c_str());
	}	
		
}