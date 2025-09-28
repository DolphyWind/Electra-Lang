cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_BINARY_NAME electra)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
project(ElectraLang VERSION 1.0.0)

set(SOURCE_FILES
    src/components/ArithmeticalUnit.cpp
    src/components/Bomb.cpp
    src/components/Cable.cpp
    src/components/Cloner.cpp
    src/components/CloningDynamicComponent.cpp
    src/components/Component.cpp
    src/components/ConditionalUnit.cpp
    src/components/ConstantAdder.cpp
    src/components/ConstantPusher.cpp
    src/components/Eraser.cpp
    src/components/FileCloser.cpp
    src/components/FileOpener.cpp
    src/components/FileReader.cpp
    src/components/FileWriter.cpp
    src/components/Key.cpp
    src/components/NonCloningDynamicComponent.cpp
    src/components/Portal.cpp
    src/components/Printer.cpp
    src/components/Reader.cpp
    src/components/Reverser.cpp
    src/components/StackChecker.cpp
    src/components/StackSwitcher.cpp
    src/components/Swapper.cpp

    src/utility/Argparser.cpp
    src/utility/FileDescriptorManager.cpp
    src/utility/Global.cpp
    src/utility/LineRange.cpp
    src/utility/Logger.cpp
    src/utility/StringUtilities.cpp

    src/Current.cpp
    src/Direction.cpp
    src/Electra.cpp
    src/Generator.cpp
    src/main.cpp
)

add_executable(${TARGET_BINARY_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_BINARY_NAME} PUBLIC include)

set(BOOST_REGEX_STANDALONE ON)
add_subdirectory(include/thirdparty/regex)
target_link_libraries(${TARGET_BINARY_NAME} PRIVATE Boost::regex)

if(MSVC)
    target_compile_options(${TARGET_BINARY_NAME} PRIVATE /utf-8)
endif()

install(TARGETS ${TARGET_BINARY_NAME} DESTINATION bin)
