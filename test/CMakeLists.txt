find_package(GTest REQUIRED)

set(systest_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/systest.cpp)

add_executable(systest
    ${systest_srcs})

target_link_libraries(systest
    djinn)