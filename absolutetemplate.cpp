#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define FRAME_RATE 1000.0
// Prototypes
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handle_input(GLFWwindow* window);

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }
    // Set the background color of choice.

    // Configure GLFW for OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Window", monitor, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Cursor disabled(For most cases like in FPS style, or when the cursor isn't needed.);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSwapInterval(1); // V-Sync on

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // vertices...

    // VAO, VBO, EBO...
    // Uplaod vertex data to VBO..
    // Upload index data to EBO..
    // Bind VAO to VBO...
    // glVertexAttribPointer...

    // vertexShader, fragmentShader..
    // Compile shaders..
    // Link shaders to program..
    // Delete vertex shader and fragment shader once linked..
    // glUseProgram(shaderProgram);
    // Uniform locations..

    // Main render loop.
     while (!glfwWindowShouldClose(window))
    {
        // Clear screen for next frame.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Input handling...
        handle_input(window);

        // Rendering commands...

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window; // Suppress unused parameter warning.
    (void)xpos; // Remove cast to void if mouse input is needed in the future.
    (void)ypos;
    // Do something;
    return;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void handle_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}