cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 COMPONENTS Quick Gui REQUIRED)
add_subdirectory(MathParser)

set(CALCULATOR_SOURCES
    Source/Main.cpp)

add_executable(${PROJECT_NAME} ${CALCULATOR_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE MathParser Qt6::Core Qt6::Gui Qt6::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE MathParser/Source)

qt6_add_qml_module(${PROJECT_NAME}
        URI .
        VERSION 1.0
        QML_FILES Qml/Main.qml
        SOURCES Source/Calculator.cpp Source/Calculator.hpp
        RESOURCES Resources/Fonts/Lato-Regular.ttf)

if(CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif()