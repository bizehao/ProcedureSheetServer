//
// Created by bizehao on 2019/10/31.
//
#include <iostream>
#include <fstream>
#include <io.h>


int main() {
	std::ifstream src_path("G:\\文档\\api");
	if (src_path.is_open()) {
		std::cout << "存在" << std::endl;
	} else {
		std::cout << "不存在" << std::endl;
	}
	std::string prefix = "G:/test/";
	if (_access(prefix.c_str(), 0) == -1) {//如果文件夹不存在
		速_mkdir(prefix.c_str());
	}	
		
}