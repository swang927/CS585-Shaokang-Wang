# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(lib/gtest-1.7.0)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# Unit Tests
add_executable(gTest test_project1.cpp)

# Standard linking to gtest stuff.
target_link_libraries(gTest gtest gtest_main)

# Extra linking for the project.
target_link_libraries(gTest Game)


