# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(lib/gtest-1.7.0)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# Unit Tests
add_executable(DefaultAllocator_test default_allocator_test.cpp)
add_executable(CountingAllocator_test counting_allocator_test.cpp)
add_executable(DynamicArray_test dynamic_array_test.cpp)
add_executable(Map_test map_test.cpp)
add_executable(Stackguard_test stack_guard_test.cpp)
add_executable(Json_test json_test.cpp)

# Standard linking to gtest stuff.
target_link_libraries(DefaultAllocator_test gtest gtest_main)
target_link_libraries(CountingAllocator_test gtest gtest_main)
target_link_libraries(DynamicArray_test gtest gtest_main)
target_link_libraries(Map_test gtest gtest_main)
target_link_libraries(Stackguard_test gtest gtest_main)
target_link_libraries(Json_test gtest gtest_main)


# Extra linking for the project.
target_link_libraries(DefaultAllocator_test Memory)
target_link_libraries(CountingAllocator_test Memory)
target_link_libraries(DynamicArray_test Container)
target_link_libraries(Map_test Container)
target_link_libraries(Stackguard_test Memory)
target_link_libraries(Json_test Data)


