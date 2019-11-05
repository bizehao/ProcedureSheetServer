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
        begin_time = std::chrono::system_clock::now();
        auto map = req.get_multipart_form_map();
        spdlog::info("请求 http: {}", req.raw_url());
        spdlog::info("参数: ");
        for (const auto& begin : map) {
            spdlog::info("    {:<15}{}", begin.first, begin.second);
        }
        return true;
    }

    bool after(cinatra::request& req, cinatra::response& res) {
        end_time = std::chrono::system_clock::now();
        std::chrono::microseconds timeInterval = std::chrono::duration_cast<std::chrono::microseconds>(end_time-begin_time);
        spdlog::info("返回的结果: \n{}",res.get_content());
        spdlog::info("耗时: {}微秒",timeInterval.count());
        return true;
    }

private:
    std::chrono::system_clock::time_point begin_time;
    std::chrono::system_clock::time_point end_time;
};
