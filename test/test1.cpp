//
// Created by bizehao on 2019/10/31.
//
#include <iostream>
#include <fstream>
#include <io.h>
#include "../src/utils/reflex.hpp"
#include <type_traits>

class AA {
public:
	virtual void MM() = 0;
	void say();
};

class BB : public AA {
public:
	void MM() override {};

	void spp() {
		this->say();
	}
};

void AA::say() {
	std::cout << "AA" << std::endl;
	BB* xx = static_cast<BB*>( this );
	std::cout << typeid( xx ).name() << std::endl;
}

int main() {
	BB bb;
	bb.say();
}