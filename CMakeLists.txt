cmake_minimum_required(VERSION 3.16)

project(SFMLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
add_executable(
  snake
  main.cpp
  utils.cpp)

  target_link_libraries(snake sfml-graphics sfml-window sfml-system)
configure_file(DejaVuSerif.ttf ./)