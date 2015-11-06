# Cmake version info
cmake_minimum_required (VERSION 2.8)

# use the c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#project name
project (CS585-Shaokang-Wang)

#collect all source files in current directory
aux_source_directory(. All_files)

#setup subdirectory
add_subdirectory (test)
add_subdirectory (src) 

#build exe
add_executable (Mygame ${All_files})

#add libraries
target_link_libraries (Mygame Container)
target_link_libraries (Mygame Memory)
target_link_libraries (Mygame Data)
