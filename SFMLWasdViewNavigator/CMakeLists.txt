cmake_minimum_required(VERSION 3.14)
project(SFMLWasdViewNavigator)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp Cell.h Cell.h)
add_executable(SFMLWasdViewNavigator ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(SFMLWasdViewNavigator sfml-system sfml-window sfml-graphics sfml-audio sfml-network)