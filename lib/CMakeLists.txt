set(djinn_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/System.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components/PhysicsComponents.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components/SpatialComponents.cpp)

add_library(djinn
    SHARED
    ${djinn_srcs})

target_include_directories(djinn
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc)