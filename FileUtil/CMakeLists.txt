
cmake_minimum_required(VERSION 3.4.1)

SET(srcDir FileUtil.c)

add_library(FileUtil STATIC ${srcDir}) # 生成动态链接库


SET(source Main.c)

add_executable(a ${source})
target_link_libraries(a FileUtil)
