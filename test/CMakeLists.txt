set(systest_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/systest.cpp)

add_executable(systest
    ${systest_srcs})

target_link_libraries(systest
    djinn)

set(timetest_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/timetest.cpp)

add_executable(timetest
    ${timetest_srcs})

target_link_libraries(timetest
    djinn)