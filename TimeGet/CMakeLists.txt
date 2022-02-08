
cmake_minimum_required (VERSION 3.8)

add_executable (TimeClient "timeclient.c" common.h)
add_executable (TimeServer "timeserver.c" common.h)
