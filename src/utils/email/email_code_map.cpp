#include "email_code_map.h"

bzh::email_code& bzh::email_code::getInstance() {
	static bool isInstance = false;
	static std::mutex mux;
	static asio::io_context io;
	static bzh::email_code emailCode(io);
	if (!isInstance) {
		std::lock_guard<std::mutex> lg(mux);
		if (!isInstance) {
			std::thread _thread([&]() {
				emailCode.exec();
				});
			_thread.detach();
			isInstance = true;
		}
	}
	return emailCode;
}

void bzh::email_code::put(const std::string& key,const email_code_model& value) {
	std::unique_lock<std::shared_mutex> _unique_lock(_shard_mutex);
	map[key] = value;
	if (!isExecued) {
		ms = 60;
		isExecued = true;
	}
	_cva.notify_all();
}

std::string bzh::email_code::get(std::string& key) {
	std::shared_lock<std::shared_mutex> _shared_lock(_shard_mutex);
	auto item = map.find(key);
	if (item != map.end()) {
		return item->second.code;
	} else {
		return "";
	}
}

void bzh::email_code::exec() {
	while (true) {
		std::shared_lock<std::shared_mutex> _shared_lock(_shard_mutex);
		while (map.empty()) {
			isExecued = false;
			_cva.wait(_shared_lock);
		}
		_shared_lock.unlock();
		_timer.expires_after(std::chrono::seconds(ms));
		_timer.wait();
		std::unique_lock<std::shared_mutex> _unique_lock(_shard_mutex);
		std::cout << "test test" << std::endl;
		for (auto& item : map) {
			if (item.second.initDate + std::chrono::seconds(60) < std::chrono::system_clock::now()) {
				destruction.push_back(item.first);
			}
		}

		for (auto& key : destruction) {
			std::cout << "delete: " << key << std::endl;
			map.erase(key);
		}
		destruction.clear();
		ms = 1;
		_cva.notify_all();
	}
}


