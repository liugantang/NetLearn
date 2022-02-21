cmake_minimum_required (VERSION 3.8)



include_directories(../Common)
link_directories(../cmake-build-debug/Common)

add_executable (EchoStrServer "echostrserver.c")
target_link_libraries(EchoStrServer libcommon.a)

add_executable(EchoStrClient "echostrclient.c" strcli.h)
target_link_libraries(EchoStrClient libcommon.a)

add_executable(EchoStr5Clients "echostr5client.c" strcli.h)
target_link_libraries(EchoStr5Clients libcommon.a)
