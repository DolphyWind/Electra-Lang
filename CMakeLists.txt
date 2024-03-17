cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_BINARY_NAME electra)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
project(ElectraLang VERSION 1.0.0)
option(ENABLE_VISUAL_MODE "Enables the visual mode" ON)

if(ENABLE_VISUAL_MODE)
    if(MSVC OR WIN32)
        add_subdirectory(include/thirdparty/pdcurses)
        set(HAS_PDCURSES TRUE)
        message("Found PDCurses")
    else()
        find_package(Curses)
        if(CURSES_FOUND)
            set(HAS_NCURSES TRUE)
            message("Found NCurses")
        else()
            message("NCurses library is not found, disabling visual Mode")
            set(ENABLE_VISUAL_MODE OFF)
        endif()
    endif()
endif()

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

# Add more source files if ENABLE_VISUAL_MODE is on
if(ENABLE_VISUAL_MODE)
    list(APPEND SOURCE_FILES
        src/visualmode/Camera.cpp
        src/visualmode/VisualInputOutputHandler.cpp
    )
endif()

# Define Target
add_executable(${TARGET_BINARY_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_BINARY_NAME} PUBLIC include)

# Boost::Regex
set(BOOST_REGEX_STANDALONE ON)
add_subdirectory(include/thirdparty/regex)
target_link_libraries(${TARGET_BINARY_NAME} PRIVATE Boost::regex)

# Set utf-8 flag if the compiler toolchain is MSVC
if(MSVC)
    target_compile_options(${TARGET_BINARY_NAME} PRIVATE /utf-8)
endif()

# Visual Mode Definitions and Linkings
if(HAS_PDCURSES)
    target_link_libraries(${TARGET_BINARY_NAME}
        PRIVATE
        PDCurses
    )
    target_compile_definitions(${TARGET_BINARY_NAME}
        PRIVATE
        HAS_PDCURSES
    )
endif()
if(HAS_NCURSES)
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
endif()
if(ENABLE_VISUAL_MODE)
    target_compile_definitions(${TARGET_BINARY_NAME}
        PRIVATE
        HAS_VISUAL_MODE
    )
endif()

# For Installation
install(TARGETS ${TARGET_BINARY_NAME} DESTINATION bin)
