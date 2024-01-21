cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(ElectraLang VERSION 1.0.0)

file(GLOB SOURCE_FILES "./src/*.cpp")
add_executable(electra ${SOURCE_FILES})

target_include_directories(electra PUBLIC include)
if(NOT WIN32)
    install(TARGETS electra DESTINATION bin)
endif()
