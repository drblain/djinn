set(djinn_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Time.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sync/Mutex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sync/Thread.cpp)

add_library(djinn
    SHARED
    ${djinn_srcs})

target_include_directories(djinn
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc)