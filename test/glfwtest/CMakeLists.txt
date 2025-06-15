add_executable(glfwtest
    glfwtest.cpp)

target_link_libraries(glfwtest
    PRIVATE
    OpenGL::GL
    glfw)