cmake_minimum_required(VERSION 3.10.2)

project(manyak_project)

set(SOURCE src/main.cpp src/logger.cpp src/environment.cpp)

find_library(SDL_2 SDL2)
if (NOT SDL_2)
  message(FATAL_ERROR "SDL2 could not be found")
endif()

find_library(SDL_2_image SDL2_image)
if (NOT SDL_2_image)
  message(FATAL_ERROR "SDL2_image could not be found")
endif()

set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")

add_executable(${PROJECT_NAME} ${SOURCE}) 

target_link_libraries(${PROJECT_NAME} ${SDL_2} ${SDL_2_image})
