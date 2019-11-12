# CMakeList.txt: ProcedureSheetServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.14)
project(ProcedureSheetServer)
set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_BUILD_TYPE Release)
#关闭编译器优化
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #add_compile_options(-fno-elide-constructors -Wall)
endif ()

#使用mysql
add_definitions(-DORMPP_ENABLE_MYSQL)
#使用spdlog的库链接方式
add_definitions(-DSPDLOG_COMPILED_LIB)

find_package(asio REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)
find_package(Cpp-Taskflow REQUIRED)

source_group("src" FILES "src/ProcedureSheetServer.cpp" "src/ProcedureSheetServer.h")
file(GLOB _base_files "src/base/*.h" "src/base/*.hpp" "src/base/*.cpp")
source_group("src/base" FILES ${_base_files})
file(GLOB _controller_files "src/controller/*.h" "src/controller/*.hpp" "src/controller/*.cpp")
source_group("src/controller" FILES ${_controller_files})
file(GLOB _entity_files "src/entity/*.h" "src/entity/*.hpp" "src/entity/*.cpp")
source_group("src/entity" FILES ${_entity_files})
file(GLOB _mapper_files "src/mapper/*.h" "src/mapper/*.hpp" "src/mapper/*.cpp")
source_group("src/mapper" FILES ${_mapper_files})
file(GLOB _utils_files "src/utils/*.h" "src/utils/*.hpp" "src/utils/*.cpp" "src/utils/*/*.h" "src/utils/*/*.hpp" "src/utils/*/*.cpp")
source_group("src/utils" FILES ${_utils_files})
file(GLOB _websocket_files "src/websocket/*.h" "src/websocket/*.hpp" "src/websocket/*.cpp")
source_group("src/websocket" FILES ${_websocket_files})

# 将源代码添加到此项目的可执行文件。
add_executable(ProcedureSheetServer "src/ProcedureSheetServer.cpp" "src/ProcedureSheetServer.h")
target_sources(ProcedureSheetServer
        PRIVATE
        ${_base_files}
        ${_controller_files}
		${_entity_files}
		${_mapper_files}
		${_utils_files}
		${_websocket_files}
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

# TODO: 如有需要，请添加测试并安装目标.
target_link_libraries(ProcedureSheetServer 
						PRIVATE 
						asio::asio 
						nlohmann_json::nlohmann_json 
						spdlog::spdlog 
						Cpp-Taskflow::Cpp-Taskflow)

add_executable(test1 test/test1.cpp)
target_include_directories(test1 PRIVATE "thirdParty")
target_link_libraries(test1 
						PRIVATE 
						asio::asio
						nlohmann_json::nlohmann_json
						)