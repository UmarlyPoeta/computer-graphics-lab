cmake_minimum_required(VERSION 3.15)
project(lab6)
add_lab(lab6 main.cpp)
#add_lab(lab6_exercise exercise/main_exercise.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

target_sources(lab6 PRIVATE ${SRC_FILES})
target_link_libraries(lab6 PRIVATE OpenGL::GL)