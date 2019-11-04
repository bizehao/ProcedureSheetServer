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

    template<typename T>
    struct remove_pointer_type;

    template<typename ...Type, typename ...Name>
    struct remove_pointer_type<std::tuple<Type Name:: * ...>> {
        using type = std::tuple<Type...>;
    };

    template<typename T>
    constexpr auto getEntityForTup(T&& t) {
        using M = decltype( iguana_reflect_members(std::forward<T>(t)) );
        return M::apply_impl();
    }

    //自定义sql查询 类型字段映射
    template<typename T, typename SQL>
    std::vector<T> customizeQuery(ormpp::dbng<ormpp::mysql>& mysql, SQL&& sql) {
        using DefType = typename remove_pointer_type<decltype( bzh::getEntityForTup(T()) )>::type;
        auto result = mysql.query<DefType>(sql);
        std::vector<T> datas;
        for (auto& itemResult : result) {
            T t;
            iguana::for_each(t, [&t, &itemResult](auto item, auto i) {
                constexpr auto Idx = decltype( i )::value;
                t.*item = std::get<Idx>(itemResult);
            });
            datas.push_back(t);
        }
        return std::move(datas);
    }
}

