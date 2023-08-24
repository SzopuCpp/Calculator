cmake_minimum_required(VERSION 3.26)
project(MathParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
        Source/MathParser/Parser/Token.hpp
        Source/MathParser/Parser/Token.cpp
        Source/MathParser/MathParser.hpp
        Source/MathParser/MathParser.cpp)

