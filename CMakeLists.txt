cmake_minimum_required(VERSION 3.10)
project(DigitalesDharmaSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(DigitalesDharmaSim
    main.cpp
    agent.cpp
    environment.cpp
)

target_include_directories(DigitalesDharmaSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
