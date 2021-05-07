cmake_minimum_required(VERSION 3.16)

project(SFMLTest)

set(CMAKE_CXX_STANDARD 17)
add_executable(
  snake
  main.cpp
  utils.cpp)

  target_link_libraries(snake sfml-graphics sfml-window sfml-system)
configure_file(DejaVuSerif.ttf ./)