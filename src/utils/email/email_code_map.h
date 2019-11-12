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
#include <optional>

namespace bzh {

    class email_code {

    public:
        explicit email_code(asio::io_context& io) : _timer(io), ms(0) {};

        ~email_code() = default;

        struct email_code_model {
            std::chrono::system_clock::time_point initDate;
            std::string code;
        };

        static bzh::email_code& getInstance();

        void put(const std::string& key,const email_code_model& value);

        std::optional<std::string> get(std::string& key);

        void exec();

    private:

        std::shared_mutex _shard_mutex;
        std::condition_variable_any _cva;
        asio::steady_timer _timer;
        std::map<std::string, email_code_model> map;
        bool isExecued = false; //当前的执行状态
        std::vector<std::string> destruction;
        int ms;//存活时间
    };
}

