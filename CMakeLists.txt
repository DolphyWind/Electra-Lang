cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_BINARY_NAME electra)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
project(ElectraLang VERSION 1.0.0)
option(ENABLE_VISUAL_MODE "Enables the visual mode" ON)

#file(GLOB SOURCE_FILES "./src/*.cpp")
set(SOURCE_FILES
    src/Argparser.cpp
    src/ArithmeticalUnit.cpp
    src/Bomb.cpp
    src/Cable.cpp
    src/Cloner.cpp
    src/CloningDynamicComponent.cpp
    src/Component.cpp
    src/ConditionalUnit.cpp
    src/ConstantAdder.cpp
    src/ConstantPusher.cpp
    src/Current.cpp
    src/Direction.cpp
    src/Electra.cpp
    src/Eraser.cpp
    src/FileCloser.cpp
    src/FileDescriptorManager.cpp
    src/FileOpener.cpp
    src/FileReader.cpp
    src/FileWriter.cpp
    src/Generator.cpp
    src/Global.cpp
    src/Key.cpp
    src/LineRange.cpp
    src/Logger.cpp
    src/main.cpp
    src/NonCloningDynamicComponent.cpp
    src/Portal.cpp
    src/Printer.cpp
    src/Reader.cpp
    src/Reverser.cpp
    src/StackChecker.cpp
    src/StackSwitcher.cpp
    src/StringUtilities.cpp
    src/Swapper.cpp
)

add_executable(${TARGET_BINARY_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_BINARY_NAME} PUBLIC include)

set(BOOST_REGEX_STANDALONE ON)
add_subdirectory(include/thirdparty/regex)
target_link_libraries(${TARGET_BINARY_NAME} PRIVATE Boost::regex)

if(MSVC)
    target_compile_options(${TARGET_BINARY_NAME} PRIVATE /utf-8)
endif()

if(ENABLE_VISUAL_MODE)
    if(MSVC OR WIN32)
        add_subdirectory(include/thirdparty/pdcurses)
        target_link_libraries(${TARGET_BINARY_NAME}
            PRIVATE
            PDCurses
        )
        target_compile_definitions(${TARGET_BINARY_NAME}
            PRIVATE
            HAS_PDCURSES
        )
        message("Found PDCurses")
    else()
        find_package(Curses REQUIRED)
        if(CURSES_FOUND)
            target_include_directories(${TARGET_BINARY_NAME}
                PRIVATE
                ${CURSES_INCLUDE_DIRS}
            )
            target_link_libraries(${TARGET_BINARY_NAME}
                PRIVATE
                ${CURSES_LIBRARIES}
            )
            target_compile_definitions(${TARGET_BINARY_NAME}
                PRIVATE
                HAS_NCURSES
            )
            message("Found NCurses")
        else()
            message(FATAL_ERROR "NCurses library is not found")
        endif()
    endif()
    target_compile_definitions(${TARGET_BINARY_NAME}
        PRIVATE
        HAS_VISUAL_MODE
    )
endif()

install(TARGETS ${TARGET_BINARY_NAME} DESTINATION bin)
