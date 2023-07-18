cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sfml_snake)

set(BUILD_SHARED_LIBS FALSE)
set(SFML_STATIC_LIBRARIES TRUE)
add_subdirectory("lib/SFML")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(sfml_snake src/main.cpp src/snake.cpp)

target_link_libraries(sfml_snake PRIVATE sfml-window sfml-audio sfml-main sfml-network sfml-graphics sfml-system)
