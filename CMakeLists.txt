cmake_minimum_required(VERSION 3.10.2)

# NOTE: While writing functions ensure that you're correctly outputting to a parent scope

# Gets all the directories within the ${curr_dir} directory
# this will reset the Variable ${output_list} and turn it into a list result of this function 
function(get_all_directories output_list curr_dir)

    file(GLOB all_files ${curr_dir}/*)

    set(temp_list "")
    foreach(file ${all_files})
        if(IS_DIRECTORY ${file})
            get_filename_component(dir_name ${file} NAME)
            list(APPEND temp_list ${dir_name})
        endif()
    endforeach()
    set(${output_list} ${temp_list} PARENT_SCOPE)
endfunction()

function(gather_current_files cpp_list hpp_list source_group_prefix curr_dir)
    # find all files needed in subdirectory
    file(GLOB found_cpp "${curr_dir}/*.cpp")
    file(GLOB found_hpp "${curr_dir}/*.hpp")

    # specify a source group for all of these files
    set(found_files "")
    list(APPEND found_files ${found_cpp})
    list(APPEND found_files ${found_hpp})
    source_group(${source_group_prefix} FILES ${found_files})

    # update 
    set(${cpp_list} ${found_cpp} PARENT_SCOPE)
    set(${hpp_list} ${found_hpp} PARENT_SCOPE)

    # include this directory for includes
    include_directories(${curr_dir})
endfunction()

function(gather_all_files_under_subdirectory cpp_list hpp_list source_group_prefix curr_dir)
    message("Processing folder ${curr_dir}")
    gather_current_files(temp_cpp_list temp_hpp_list ${source_group_prefix} ${curr_dir})

    # recurse into all subdirectories
    get_all_directories(sub_dirs ${curr_dir})
    foreach(sub_dir ${sub_dirs})
        gather_all_files_under_subdirectory(temp_sub_cpp_list temp_sub_hpp_list "${source_group_prefix}/${sub_dir}" "${curr_dir}/${sub_dir}")
        list(APPEND temp_cpp_list ${temp_sub_cpp_list})
        list(APPEND temp_hpp_list ${temp_sub_hpp_list})
    endforeach()
    set(${cpp_list} ${temp_cpp_list} PARENT_SCOPE)
    set(${hpp_list} ${temp_hpp_list} PARENT_SCOPE)
endfunction()

project (manyak_engine)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    include (${CMAKE_SOURCE_DIR}/3rdParty/vcpkg/scripts/buildsystems/vcpkg.cmake)
    set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> /EHsc /nologo <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>")
    set(CMAKE_CXX_COMPILE_OBJECT "<CMAKE_CXX_COMPILER> /EHsc /nologo /TP <DEFINES> <INCLUDES> <FLAGS> /Fo<OBJECT> /FS -c <SOURCE>")

    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

    include_directories(3rdParty/SDL2-2.0.12/include
                        3rdParty/SDL2_image-2.0.5/include
                        3rdParty/SDL2_ttf-2.0.15/include)

    add_definitions(-DMANYAK_WIN32)
    add_definitions(-DRUNNING_MANYAK_GAME="./Debug/temp_manyakGame.dll")
else()
    add_definitions(-DMANYAK_MAC)
    add_definitions(-DRUNNING_MANYAK_GAME="./temp_manyakGame")
endif()

if (WIN32)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(sdl2-image CONFIG REQUIRED)
    find_package(sdl2-ttf CONFIG REQUIRED)
    set(ALL_SDL2_LIBRARY_TARGETS "SDL2::SDL2;SDL2::SDL2main;SDL2::SDL2_image;SDL2::SDL2_ttf")
    find_package(unofficial-box2d CONFIG REQUIRED)
    set(BOX2D_LIBRARY_TARGET "unofficial::box2d::box2d")
else()
    find_library(SDL_2 SDL2)
    if (NOT SDL_2)
        message(FATAL_ERROR "SDL2 could not be found")
    endif()
    find_library(SDL_2_image SDL2_image)
    if (NOT SDL_2_image)
      message(FATAL_ERROR "SDL2_image could not be found")
    endif()
    find_library(SDL_2_ttf SDL2_ttf)
    if (NOT SDL_2_ttf)
        message(FATAL_ERROR "SDL2_ttf could not be found")
    endif()

    set(ALL_SDL2_LIBRARY_TARGETS "${SDL_2};${SDL_2_image};${SDL_2_ttf}")

    find_package(box2d REQUIRED)
    set(BOX2D_LIBRARY_TARGET "box2d")
endif()

if(WIN32)
    #file(GLOB DLLS "3rdParty/SDL2-2.0.12/lib/x64/*.dll" "3rdParty/SDL2_image-2.0.5/lib/x64/*.dll" "3rdParty/SDL2_ttf-2.0.15/lib/x64/*.dll")
    
    set (CMAKE_CXX_FLAGS "/std:c++17 /EHsc")
else()
    set (CMAKE_CXX_FLAGS "-Wall -Werror -std=c++17 -stdlib=libc++")
endif()

gather_all_files_under_subdirectory(ENGINE_CPP_FILES ENGINE_HPP_FILES "Files" "${PROJECT_ROOT}/src/engine")

add_library(manyak_engine STATIC ${ENGINE_CPP_FILES} ${ENGINE_HPP_FILES})

target_link_libraries(manyak_engine ${ALL_SDL2_LIBRARY_TARGETS} ${BOX2D_LIBRARY_TARGET})

function(build_game game)
    project(${game})
    add_definitions(-DGAME_RESOURCE_DIR="${PROJECT_ROOT}/resources/${game}/")

    gather_all_files_under_subdirectory(GAME_CPP_FILES GAME_HPP_FILES "Files" "${PROJECT_ROOT}/src/games/${game}")

    add_executable(${game} ${GAME_CPP_FILES} ${GAME_HPP_FILES}) 

    target_link_libraries(${game} manyak_engine)
endfunction()

get_all_directories(games_list "${PROJECT_ROOT}/src/games")
foreach(game ${games_list})
    build_game(${game})
endforeach()

#if(WIN32)
    # copy the .dll files to the same folder as the executable
    #foreach(DLL ${DLLS})
        #add_custom_command(TARGET manyak_game POST_BUILD
            #COMMAND ${CMAKE_COMMAND} -E copy_if_different
            #${DLL}
            #$<TARGET_FILE_DIR:manyak_game>)
    #endforeach(DLL)
#endif()
