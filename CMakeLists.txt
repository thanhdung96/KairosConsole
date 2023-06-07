cmake_minimum_required(VERSION 3.25)
project(KairosConsole)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lcurl")
set(CMAKE_PREFIX_PATH "/home/thanhdung/Qt5.12.12/5.12.12")

find_package(Qt5 REQUIRED COMPONENTS Widgets)
include_directories(include KairosQt/include)
file(GLOB_RECURSE SOURCE_DIR "src/*.cpp")
file(GLOB_RECURSE SOURCE_QT_DIR "KairosQt/src/*.cpp")

add_executable(
        KairosConsole
        main.cpp
        ${SOURCE_DIR}
        ${SOURCE_QT_DIR}
)

target_link_libraries(KairosConsole Qt5::Widgets)
