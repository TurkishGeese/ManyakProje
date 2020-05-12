cmake_minimum_required(VERSION 3.10.2)

project (manyak_game)

file(GLOB_RECURSE SOURCE "src/*.cpp")
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if (WIN32)
    set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER>  /nologo <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>")
    set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER>  /nologo /TP <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>")
endif()

if(WIN32)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

    include_directories(3rdParty/SDL2-2.0.12/include
                        3rdParty/SDL2_image-2.0.5/include
                        3rdParty/SDL2_ttf-2.0.15/include
                        src
                        src/levels
                        src/objects
                        src/objects/gameObjects
                        src/objects/uiObjects
                        src/inputConfigurations)

    add_definitions(-DMANYAK_WIN32)
    add_definitions(-DRUNNING_MANYAK_GAME="./temp_manyakGame.dll")
else()
    include_directories(src
                        src/levels
                        src/objects
                        src/objects/gameObjects
                        src/objects/uiObjects
                        src/inputConfigurations)
    add_definitions(-DMANYAK_MAC)
    add_definitions(-DRUNNING_MANYAK_GAME="./temp_manyakGame")
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

if (WIN32)
    find_library(SDL_2_ttf NAMES SDL2_ttf PATHS 3rdParty/SDL2_ttf-2.0.15/lib/x64)
else()
    find_library(SDL_2_ttf SDL2_ttf)
endif()
if (NOT SDL_2_ttf)
  message(FATAL_ERROR "SDL2_ttf could not be found")
endif()

if(WIN32)
    file(GLOB DLLS "3rdParty/SDL2-2.0.12/lib/x64/*.dll" "3rdParty/SDL2_image-2.0.5/lib/x64/*.dll" "3rdParty/SDL2_ttf-2.0.15/lib/x64/*.dll")
    
    set (CMAKE_CXX_FLAGS "/std:c++17")
else()
    set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17 -stdlib=libc++")
endif()

add_library(manyak_game SHARED ${SOURCE})

if (WIN32)
    # TODO FIGURE OUT PROPERLY HOTLOADING IN WINDOWS
    # Note that these are left here as a reminder for the next time.
    #string(TIMESTAMP TODAY "%H:%M:%S%d%m%Y")
    #string(CONCAT MANYAK_GAME_LIB_NAME "CMakeFiles\\manyak_game.dir\\manyak_game" ${TODAY})
    #set(TARGET_PDB ${MANYAK_GAME_LIB_NAME})
    #set(TARGET_COMPILE_PDB ${MANYAK_GAME_LIB_NAME})
    #set_target_properties(manyak_game PROPERTIES
    #    PDB_NAME ${MANYAK_GAME_LIB_NAME}
    #    CMAKE_PDB_OUTPUT_DIRECTORY ${MANYAK_GAME_LIB_NAME}
    #    CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${MANYAK_GAME_LIB_NAME})
    #target_compile_options(manyak_game PRIVATE /Fd:${MANYAK_GAME_LIB_NAME} /PDB:manyak_%random%.pdb /PDBALTPATH:manyak_%random%.pdb)
    #set_target_properties(manyak_game PROPERTIES
    #    TARGET_COMPILE_PDB ${MANYAK_GAME_LIB_NAME}
    #    CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER>  /nologo <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>"
    #    CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER>  /nologo /TP <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>")
    #
    #get_target_property(targetCompileFlags manyak_game CMAKE_CXX_COMPILE_OBJECT)
endif()

# TODO manyak_project doesn't need to be linked against SDL libraries - SDL2
target_link_libraries(manyak_game ${SDL_2} ${SDL_2_image} ${SDL_2_ttf})

project(manyak_project)

add_executable(manyak_project "src/main.cpp" "src/logger.cpp") 

target_link_libraries(manyak_project manyak_game ${SDL_2} ${SDL_2_image} ${SDL_2_ttf})

if(WIN32)
    # copy the .dll files to the same folder as the executable
    foreach(DLL ${DLLS})
        add_custom_command(TARGET manyak_game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL}
            $<TARGET_FILE_DIR:manyak_game>)
    endforeach(DLL)
endif()

#########################################################################################################################
# This part is very helpful while debugging CMAKE. It has a lot of predefined variables and this part prints everything.
# It helps with finding where certaing flags are coming from.


#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()


#########################################################################################################################
# Similarly this does the same thing but for a specific target.

# Get all propreties that cmake supports
#execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
#
## Convert command output into a CMake list
#STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#
#function(print_properties)
#    message ("CMAKE_PROPERTY_LIST = ${CMAKE_PROPERTY_LIST}")
#endfunction(print_properties)
#
#function(print_target_properties tgt)
#    if(NOT TARGET ${tgt})
#      message("There is no target named '${tgt}'")
#      return()
#    endif()
#
#    foreach (prop ${CMAKE_PROPERTY_LIST})
#        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
#    # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
#    if(prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
#        continue()
#    endif()
#        # message ("Checking ${prop}")
#        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
#        if (propval)
#            get_target_property(propval ${tgt} ${prop})
#            message ("${tgt} ${prop} = ${propval}")
#        endif()
#    endforeach(prop)
#endfunction(print_target_properties)
#
#print_target_properties(manyak_game)