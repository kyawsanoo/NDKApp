cmake_minimum_required(VERSION 3.22.1)
project("ndkapp")
add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)
add_library(hello-lib SHARED
        hello-lib.c)
target_link_libraries(${CMAKE_PROJECT_NAME}
        hello-lib
        android
        log)