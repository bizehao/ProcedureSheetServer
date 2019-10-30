//
// Created by bizehao on 2019/10/30.
//

#pragma once

#include <vector>
#include <tuple>
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "ormpp/reflection.hpp"

namespace bzh {

    //自定义sql查询
    /*template<typename T, typename SQL>
    std::vector<T> customizeQuery(ormpp::dbng<ormpp::mysql>& mysql, SQL&& sql) {
        constexpr auto SIZE = iguana::get_value<T>();
        T t;
        iguana::for_each(t, [&mp, &t](auto item, auto i) {
            using U = std::remove_reference_t<decltype(std::declval<T>().*item)>;
            if constexpr (std::is_same_v<std::string, U>) {
                auto& vec = mp[decltype(i)::value];
                t.*item = std::string(&vec[0], strlen(vec.data()));
            }
            else if constexpr(is_char_array_v<U>) {
                auto& vec = mp[decltype(i)::value];
                memcpy(t.*item, vec.data(), vec.size());
            }
        });

        result = mysql.query<std::tuple<>>(sql);
    }*/
}

