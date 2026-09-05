add_executable(test_unique_ptr unique_ptr.cpp)
target_link_libraries(test_unique_ptr PRIVATE mystl)
add_test(NAME test_unique_ptr COMMAND test_unique_ptr)
