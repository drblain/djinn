set(gamedjinn_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/System.cpp)

add_library(gamedjinn
    ${gamedjinn_srcs})

target_include_directories(gamedjinn
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc)