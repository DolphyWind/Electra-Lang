cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

project(ElectraLang VERSION 1.0.0)

file(GLOB SOURCE_FILES "./src/*.cpp")
if(WIN32)
    add_executable(electra WIN32 ${SOURCE_FILES})
else()
    add_executable(electra ${SOURCE_FILES})
endif()

target_include_directories(electra PUBLIC include)
if(NOT WIN32)
    install(TARGETS electra DESTINATION bin)
endif()
