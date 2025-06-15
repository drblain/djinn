set(djinn_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/System.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Time.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/entities/PlayerEntity.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sync/Mutex.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sync/Thread.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/InputSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/systems/RenderSystem.cpp)

add_library(djinn
    SHARED
    ${djinn_srcs})

target_include_directories(djinn
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(djinn
    PRIVATE
    OpenGL::GL
    glfw)