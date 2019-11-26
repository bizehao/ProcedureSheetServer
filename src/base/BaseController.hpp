//
// Created by bizehao on 2019/10/31.
//

#pragma once

#include <cinatra/http_server.hpp>
#include "../mapper/UserMapper.h"
#include "../utils/currency_net.hpp"
#include <functional>
#include "../utils/my_util.hpp"
#include "../utils/json_util.hpp"

//重扫描
#define RE_SCANNING(...) __VA_ARGS__

//to string
#define TO_STRING_(a) #a
#define TO_STRING(a) TO_STRING_(a)

//定义那个类
#define CLASS_TYPE

//方法的参数
#define REQ_ARGS(...) RE_SCANNING(FOR_EACH_COMMA(TO_STRING, __VA_ARGS__))

//添加
#define APPEND_REQUEST(...) baseExecNet(*this, ##__VA_ARGS__);

//第一个请求头  第二个请求的方法地址 剩余的为参数字段名   
#define SV_HAVE_GINSENG(REQ_ADDRESS, REQ_TYPE, REQ_METHOD, ...) std::make_tuple(REQ_ADDRESS, REQ_TYPE{}, &CLASS_TYPE::REQ_METHOD, REQ_ARGS(__VA_ARGS__))
//无参
#define SV_No_GINSENG(REQ_ADDRESS, REQ_TYPE, REQ_METHOD) std::make_tuple(REQ_ADDRESS, REQ_TYPE{}, &CLASS_TYPE::REQ_METHOD)

#define GetMacro(__a,__b, \
				 _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
				_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
				_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
				_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
				_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
				_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
				_61,_62,_63,_64,_65,_66,_67,_68,_69,_70, \
				_71,_72,_73,_74,_75,_76,_77,_78,_79,_80, \
				_81,_82,_83,_84,_85,_86,_87,_88,_89,_90, \
				_91,_92,_93,_94,_95,_96,_97,_98,_99, NAME, ...) NAME

#define GINSENG_Method() \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, A, A, \
		A, A, A, A, A, A, A, A, B

#define A SV_HAVE_GINSENG
#define B SV_No_GINSENG

#define SV_(...) RE_SCANNING(GetMacro(__VA_ARGS__))
#define SV(...) SV_(__VA_ARGS__, GINSENG_Method())RE_SCANNING((__VA_ARGS__))

struct HttpGet {
	static constexpr auto reqMethod = cinatra::GET;
};

struct HttpPost {
	static constexpr auto reqMethod = cinatra::POST;
};

class BaseController {
public:
	BaseController(cinatra::http_server& server) : server(server) {}

	virtual void exec() = 0;

	virtual ~BaseController() = default;

protected:

	template<typename OBJ, typename... T>
	void baseExecNet(OBJ& obj, T... t) {
		execNet(obj, server, t...);
	}

	cinatra::http_server& server;
};
