cmake_minimum_required(VERSION 3.10.2)

project (manyak_game)

file(GLOB SOURCE "src/*.cpp")
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(WIN32)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")

    include_directories(3rdParty/SDL2-2.0.12/include 3rdParty/SDL2_image-2.0.5/include)

    add_definitions(-DMANYAK_WIN32)
else()
    add_definitions(-DMANYAK_MAC)
endif()
add_definitions(-DMANYAK_GAME="$<TARGET_FILE:manyak_game>")

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

    set (OLD_FLAGS ${CMAKE_CXX_FLAGS})
    set (CMAKE_CXX_FLAGS "/std:c++17 -PDB:manyak_game%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~0,2%%time:~3,2%%time:~6,2%.pdb")
else()
    set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17")
endif()

add_library(manyak_game SHARED ${SOURCE})

target_link_libraries(manyak_game ${SDL_2} ${SDL_2_image})

project(manyak_project)

if(WIN32)
    set (CMAKE_CXX_FLAGS ${OLD_FLAGS})
    set (CMAKE_CXX_FLAGS "/std:c++17")
endif()

add_executable(manyak_project "src/main.cpp" "src/logger.cpp") 

target_link_libraries(manyak_project manyak_game ${SDL_2} ${SDL_2_image})

if(WIN32)
    # copy the .dll files to the same folder as the executable
    foreach(DLL ${DLLS})
        add_custom_command(TARGET manyak_game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL}
            $<TARGET_FILE_DIR:manyak_game>)
    endforeach(DLL)
endif()