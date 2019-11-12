//
// Created by bizehao on 2019/10/30.
//

#pragma once

#include <vector>
#include <tuple>
#include "ormpp/dbng.hpp"
#include "ormpp/mysql.hpp"
#include "ormpp/reflection.hpp"
#include <queue>
#include <optional>

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
	template<typename T, typename ...Args>
	std::vector<T> customizeQuery(ormpp::dbng<ormpp::mysql>& mysql, std::string&& sql, Args... args) {
		using DefType = typename remove_pointer_type<decltype( bzh::getEntityForTup(T()) )>::type;
		auto result = mysql.query<DefType>(sql, std::forward<Args>(args)...);
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

	//单个列的单个值的查询
	template<typename T, typename ...Args>
	std::optional<T> customizeQueryOfSingle(ormpp::dbng<ormpp::mysql>& mysql, std::string&& sql, Args... args) {
		std::queue<std::string> queue_ = tupToQueue(std::make_tuple(args...), std::index_sequence_for<Args...>());
		handlePlaceholder(sql, queue_);
		auto result = mysql.query<std::tuple<T>>(sql);
		std::optional<T> t;
		if (!result.empty()) {
			t = std::get<0>(result[0]);
		}
		return std::move(t);
	}
	//自定义增删改
	template<typename ...Args>
	bool customizeCUD(ormpp::dbng<ormpp::mysql>& mysql, std::string&& sql, Args... args) {
		std::queue<std::string> queue_ = tupToQueue(std::make_tuple(args...), std::index_sequence_for<Args...>());
		handlePlaceholder(sql, queue_);
		bool xx = mysql.execute(sql);
		return xx;
	}
	//std::integral_constant<>

	//元组转为栈
	template<typename Tup, size_t ...N>
	std::queue<std::string> tupToQueue(Tup&& tup, std::index_sequence<N...>) {
		std::queue<std::string> queue_;
		( queue_.push(std::is_same_v<std::decay_t<std::tuple_element_t<N, Tup>>, std::string> ? std::get<N>(tup) : static_cast<std::string>( std::get<N>(tup) )), ... );
		return std::move(queue_);
	}
	//处理占位符
	void handlePlaceholder(std::string& sql, std::queue<std::string>& queue_) {
		int position = 0;
		while (position < sql.size()) {
			auto index = sql.find('?', position);
			if (index != std::string::npos) {
				std::string vv = "'" + queue_.front() + "'";
				sql.insert(index, vv);
				sql.erase(index + vv.size(), 1);
				position = index + vv.size();
				queue_.pop();
			} else {
				position++;
			}
		}
	}
}

