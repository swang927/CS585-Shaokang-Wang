#collect all source files in current directory
aux_source_directory(. All_src_files)

#build library
add_library (Game ${All_src_files})

