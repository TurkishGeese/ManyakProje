cmake_minimum_required(VERSION 3.10.2)

project(manyak_project)

file(GLOB SOURCE "src/*.cpp")
#set(SOURCE src/main.cpp src/logger.cpp src/environment.cpp)

if(WIN32)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")

    include_directories(3rdParty/SDL2-2.0.12/include 3rdParty/SDL2_image-2.0.5/include)

    add_definitions(-DMANYAK_WIN32)
else()
    add_definitions(-DMANYAK_MAC)
endif()

if (WIN32)
    find_library(SDL_2 NAMES SDL2 PATHS 3rdParty/SDL2-2.0.12/lib/x64)
else()
    find_library(SDL_2 SDL2)
endif()
if (NOT SDL_2)
  message(FATAL_ERROR "SDL2 could not be found")
endif()


if (WIN32)
    find_library(SDL_2_image NAMES SDL2_image PATHS 3rdParty/SDL2_image-2.0.5/lib/x64)
else()
    find_library(SDL_2_image SDL2_image)
endif()
if (NOT SDL_2_image)
  message(FATAL_ERROR "SDL2_image could not be found")
endif()

if(WIN32)
    file(GLOB DLLS "3rdParty/SDL2-2.0.12/lib/x64/*.dll" "3rdParty/SDL2_image-2.0.5/lib/x64/*.dll")
else()
    set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")
endif()

add_executable(${PROJECT_NAME} ${SOURCE}) 

target_link_libraries(${PROJECT_NAME} ${SDL_2} ${SDL_2_image})

if(WIN32)
    # copy the .dll files to the same folder as the executable
    foreach(DLL ${DLLS})
        add_custom_command(TARGET manyak_project POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL}
            $<TARGET_FILE_DIR:manyak_project>)
    endforeach(DLL)
endif()