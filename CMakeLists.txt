cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_BINARY_NAME electra)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
project(ElectraLang VERSION 1.0.0)

file(GLOB SOURCE_FILES "./src/*.cpp")
add_executable(${TARGET_BINARY_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_BINARY_NAME} PUBLIC include)

set(BOOST_REGEX_STANDALONE ON)
add_subdirectory(include/thirdparty/regex)
target_link_libraries(${TARGET_BINARY_NAME} PRIVATE Boost::regex)

if(WIN32)
    target_compile_definitions(${TARGET_BINARY_NAME} PRIVATE /utf-8)
endif()

if(NOT WIN32)
    install(TARGETS ${TARGET_BINARY_NAME} DESTINATION bin)
endif()
