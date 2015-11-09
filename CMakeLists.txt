# Cmake version info
cmake_minimum_required (VERSION 2.8)
# use the c++ std 11
add_definitions(-std=c++0x)

#project name
project (Shaokang_game)

# Define sources and executable
set(EXECUTABLE_NAME "Shaokang_game")
add_executable(${EXECUTABLE_NAME} game.m.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.3.2/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
message (STATUS ${CMAKE_MODULE_PATH}) 
#Find any version 2.X of SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
    # list of files for which we add a copy rule
    set(data_SHADOW player.png)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()
endif()

# files are only copied if a target depends on them
add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/player.png")


#setup subdirectory
add_subdirectory (test)
add_subdirectory (src) 


#add libraries
target_link_libraries (${EXECUTABLE_NAME} Container)
target_link_libraries (${EXECUTABLE_NAME} Data)
target_link_libraries (${EXECUTABLE_NAME} Input)
target_link_libraries (${EXECUTABLE_NAME} Memory)
target_link_libraries (${EXECUTABLE_NAME} Rendering)
target_link_libraries (${EXECUTABLE_NAME} Scene)

