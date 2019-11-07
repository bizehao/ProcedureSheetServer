//
// Created by bizehao on 2019/10/25.
//

#pragma once

#include "cinatra.hpp"
#include "spdlog/spdlog.h"
#include <chrono>
#include <thread>

//日志切面
struct log_t {

    bool before(cinatra::request& req, cinatra::response& res) {
        begin_time = std::chrono::steady_clock::now();
        auto map = req.get_multipart_form_map();
        spdlog::info("request http: {}", req.raw_url());
        spdlog::info("args: ");
        for (const auto& begin : map) {
            spdlog::info("    {:<15}{}", begin.first, begin.second);
        }
        return true;
    }

    bool after(cinatra::request& req, cinatra::response& res) {
        end_time = std::chrono::steady_clock::now();
        std::chrono::microseconds timeInterval = std::chrono::duration_cast<std::chrono::microseconds>(end_time-begin_time);
        spdlog::info("result: \n{}",res.get_content());
        spdlog::info("time consuming: {}μs",timeInterval.count());
        return true;
    }

private:
    std::chrono::steady_clock::time_point begin_time;
    std::chrono::steady_clock::time_point end_time;
};
