# Cmake version info
cmake_minimum_required(VERSION 2.8)

#project name
project(CS585)

#collect all source files in current directory
aux_source_directory(. All_files)

#build exe
add_executable(Mytest ${All_files})

