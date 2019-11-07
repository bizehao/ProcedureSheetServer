#pragma once

#include <shared_mutex>
#include <chrono>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <asio.hpp>
#include <iostream>


namespace bzh {

	class email_code {

	public:
		email_code(asio::io_context& io) :ms(0), _timer(io) {};
		~email_code() {};

		struct email_code_model {
			std::chrono::system_clock::time_point initDate;
			std::string code;
		};

		static bzh::email_code& getInstance();

		void put(std::string key, email_code_model& value);

		std::string get(std::string& key);

		void exec();

	private:

		std::shared_mutex _shard_mutex;
		std::condition_variable_any _cva;
		asio::steady_timer _timer;
		std::map<std::string, email_code_model> map;
		bool isExecued = false; //��ǰ��ִ��״̬
		std::vector<std::string> destruction;
		int ms;//���ʱ��
	};
}

