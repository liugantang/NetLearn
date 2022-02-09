
cmake_minimum_required (VERSION 3.8)



include_directories(../Common)
link_directories(../cmake-build-debug/Common)


add_executable (TimeClient "timeclient.c")
target_link_libraries(TimeClient libcommon.a)
add_executable (TimeServer "timeserver.c")
target_link_libraries(TimeServer libcommon.a)
add_executable(TimeServerShowClient timeservershowclient.c)
target_link_libraries(TimeServerShowClient libcommon.a)