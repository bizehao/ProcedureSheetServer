#pragma once

#include "cinatra.hpp"

class MyWebSocket {
public:
	MyWebSocket() {};
	~MyWebSocket() {};

	void onOpen(cinatra::request& req);

	void onMessage(cinatra::request& req);

	void onClose(cinatra::request& req);

	void onError(cinatra::request& req);


private:

};