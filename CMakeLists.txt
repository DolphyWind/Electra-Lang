cmake_minimum_required(VERSION 3.25.2)
set(CMAKE_CXX_STANDARD 20)

project(ElectraLang VERSION 1.0.0)

file(GLOB SOURCE_FILES "./src/*.cpp")
add_executable(electra ${SOURCE_FILES})

target_include_directories(electra PRIVATE include)
