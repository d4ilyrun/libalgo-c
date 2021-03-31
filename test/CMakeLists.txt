function(add_test_suite _testName _source)
    add_executable(${_testName} ${_source})
    target_link_libraries(${_testName} ${PROJECT_NAME})
    add_test(${_testName} ${CMAKE_CURRENT_BINARY_DIR}/${_testName})
endfunction()

add_test_suite(list_tests list.c)
add_test_suite(stack_tests stack.c)
