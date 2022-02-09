cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
SET(LIBCOMMON_SRC commondetermine.h commondetermine.c)
ADD_LIBRARY(common STATIC ${LIBCOMMON_SRC})