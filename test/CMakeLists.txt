set(djinntest_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(djinntest
    ${djinntest_srcs})

target_link_libraries(djinntest
    djinn)