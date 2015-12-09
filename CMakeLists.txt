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
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.3.2" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  message (STATUS ${SFML_INCLUDE_DIR}) 
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# copy the image to work place
configure_file(image/player.png ${CMAKE_CURRENT_BINARY_DIR}/image/player.png COPYONLY)
configure_file(image/player_1.png ${CMAKE_CURRENT_BINARY_DIR}/image/player_1.png COPYONLY)
configure_file(image/blue_guard.png ${CMAKE_CURRENT_BINARY_DIR}/image/blue_guard.png COPYONLY)
configure_file(image/blue_guard_1.png ${CMAKE_CURRENT_BINARY_DIR}/image/blue_guard_1.png COPYONLY)
configure_file(image/red_guard.png ${CMAKE_CURRENT_BINARY_DIR}/image/red_guard.png COPYONLY)
configure_file(image/red_guard_1.png ${CMAKE_CURRENT_BINARY_DIR}/image/red_guard_1.png COPYONLY)
configure_file(image/Brick_Wall.png ${CMAKE_CURRENT_BINARY_DIR}/image/Brick_Wall.png COPYONLY)
configure_file(image/ninja_weapon.png ${CMAKE_CURRENT_BINARY_DIR}/image/ninja_weapon.png COPYONLY)
configure_file(image/number_sheets.png ${CMAKE_CURRENT_BINARY_DIR}/image/number_sheets.png COPYONLY)
configure_file(image/youLoss.png ${CMAKE_CURRENT_BINARY_DIR}/image/youLoss.png COPYONLY)
configure_file(image/youWin.png ${CMAKE_CURRENT_BINARY_DIR}/image/youWin.png COPYONLY)



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
target_link_libraries (${EXECUTABLE_NAME} Events)
target_link_libraries (${EXECUTABLE_NAME} Actors)
target_link_libraries (${EXECUTABLE_NAME} Controllers)

