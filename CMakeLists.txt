# CMakeList.txt: ProcedureSheetServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project(ProcedureSheetServer)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DORMPP_ENABLE_MYSQL)

message("aa：" ${PROJECT_SOURCE_DIR})

# 将源代码添加到此项目的可执行文件。
add_executable (ProcedureSheetServer "ProcedureSheetServer.cpp" "ProcedureSheetServer.h")

target_include_directories (ProcedureSheetServer PRIVATE "thirdParty")
target_link_directories (ProcedureSheetServer PRIVATE "libs")

if(WIN32)
   target_link_libraries(ProcedureSheetServer PRIVATE "libmysql")
   # Copy DLL files to output directory
   add_custom_command(TARGET ProcedureSheetServer POST_BUILD 
       COMMAND ${CMAKE_COMMAND} -E copy_if_different
       "${PROJECT_SOURCE_DIR}/libs/libmysql.dll"              
       $<TARGET_FILE_DIR:ProcedureSheetServer>)
endif()

if (UNIX)
   target_link_libraries(ProcedureSheetServer PRIVATE mysqlclient pthread)
endif ()

# TODO: 如有需要，请添加测试并安装目标。
