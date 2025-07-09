cmake_minimum_required(VERSION 3.10)
project(simulated_digital_dharma)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(simulated_digital_dharma
    main.cpp
    agent.cpp
    environment.cpp
    DecisionStrategy.cpp
)

target_include_directories(simulated_digital_dharma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
