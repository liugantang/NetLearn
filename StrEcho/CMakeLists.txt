cmake_minimum_required (VERSION 3.8)



include_directories(../Common)
link_directories(../cmake-build-debug/Common)

add_executable (EchoStrServer "echostrserver.c")
target_link_libraries(EchoStrServer libcommon.a)

add_executable(EchoStrClient "echostrclient.c")
target_link_libraries(EchoStrClient libcommon.a)
