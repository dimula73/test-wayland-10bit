cmake_minimum_required(VERSION 3.16)

project(HelloWorldQt6 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(testwayland10bit
    main.cpp
    kis_debug.cpp
    kis_assert.cpp
    kis_opengl.cpp
    KisOpenGLModeProber.cpp
    )

target_include_directories(testwayland10bit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(testwayland10bit
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
