# CMakeList.txt: ProcedureSheetServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.14)
project(ProcedureSheetServer)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_BUILD_TYPE Release)
#关闭编译器优化
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fno-elide-constructors -Wall)
endif ()

#使用mysql
add_definitions(-DORMPP_ENABLE_MYSQL)
#使用spdlog的库链接方式
add_definitions(-DSPDLOG_COMPILED_LIB)

if (WIN32)
	add_definitions(-DCMAKE_TOOLCHAIN_FILE="D:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
endif ()

# 将源代码添加到此项目的可执行文件。
add_executable(ProcedureSheetServer "src/ProcedureSheetServer.cpp" "src/ProcedureSheetServer.h")
target_sources(ProcedureSheetServer
        PRIVATE
        "src/base/BaseController.hpp"
        "src/base/BaseMapper.hpp"
        )

target_sources(ProcedureSheetServer
        PRIVATE
        "src/controller/UserController.h"
        "src/controller/UserController.cpp"
		"src/controller/CommController.h"
		"src/controller/CommController.cpp"
        )

target_sources(ProcedureSheetServer
        PRIVATE
        "src/entity/UserEntity.h"
        )

target_sources(ProcedureSheetServer
        PRIVATE
        "src/mapper/UserMapper.cpp"
        "src/mapper/UserMapper.h"
        )

target_sources(ProcedureSheetServer
        PRIVATE
        "src/utils/currency_net.hpp"
        "src/utils/currency_sql.hpp"
        "src/utils/reflex.hpp"
        "src/utils/section.h"
        "src/utils/ThreadPool.hpp"
		"src/utils/email/email.h"
		"src/utils/email/email.cpp"
		"src/utils/email/email_code_map.h"
		"src/utils/email/email_code_map.cpp"
        )

target_sources(ProcedureSheetServer
        PRIVATE
        "src/base/BaseController.hpp"
        "src/base/BaseMapper.hpp"
        )
target_include_directories(ProcedureSheetServer PRIVATE "thirdParty")
target_link_directories(ProcedureSheetServer PRIVATE "libs")

if (WIN32)
    target_link_libraries(ProcedureSheetServer PRIVATE "libmysql")
    # Copy DLL files to output directory
    add_custom_command(TARGET ProcedureSheetServer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/libs/libmysql.dll"
            $<TARGET_FILE_DIR:ProcedureSheetServer>)
endif ()

if (UNIX)
    target_link_libraries(ProcedureSheetServer PRIVATE mysqlclient pthread uuid stdc++fs)
endif ()

# TODO: 如有需要，请添加测试并安装目标。

find_package(asio CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Cpp-Taskflow CONFIG REQUIRED)

target_link_libraries(ProcedureSheetServer 
						PRIVATE 
						asio::asio 
						nlohmann_json::nlohmann_json 
						spdlog::spdlog 
						Cpp-Taskflow::Cpp-Taskflow)

add_executable(test1 src/test/test1.cpp)