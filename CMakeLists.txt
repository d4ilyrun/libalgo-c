cmake_minimum_required(VERSION 3.13)
project(libalgo VERSION 1.0.1 DESCRIPTION "A library of classic data structures.")
include(GNUInstallDirs)

# create library
add_library(${PROJECT_NAME} SHARED
        src/list.c
        src/stack.c
        src/data_types.c)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/${PROJECT_NAME}.h)
target_include_directories(${PROJECT_NAME} PRIVATE .)

# install library
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# ------------ TESTS ----------------

enable_testing()
add_subdirectory(test)
