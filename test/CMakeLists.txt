add_executable(systest
    ${CMAKE_CURRENT_SOURCE_DIR}/systest.cpp)

target_link_libraries(systest
    djinn)

add_executable(timetest
    ${CMAKE_CURRENT_SOURCE_DIR}/timetest.cpp)

target_link_libraries(timetest
    djinn)

add_executable(threadtest
    ${CMAKE_CURRENT_SOURCE_DIR}/threadtest.cpp)

target_link_libraries(threadtest
    djinn)

add_executable(enginetest
    ${CMAKE_CURRENT_SOURCE_DIR}/enginetest.cpp)

target_link_libraries(enginetest
    djinn)