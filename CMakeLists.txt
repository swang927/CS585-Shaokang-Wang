# Cmake version info
cmake_minimum_required (VERSION 2.8)

#project name
project (CS585)

#collect all source files in current directory
aux_source_directory (. All_files)

#setup subdirectory
add_subdirectory (test)
add_subdirectory (src) 

#build exe
add_executable (Mygame ${All_files})

#add libraries
target_link_libraries (Mygame Game)
