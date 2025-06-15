add_executable(rendertest
    rendertest.cpp)

target_link_libraries(rendertest
    OpenGL::GL
    glfw
    djinn)