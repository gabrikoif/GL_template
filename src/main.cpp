#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define FRAME_RATE 1000.0
// Prototypes
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void handle_input(GLFWwindow *window);

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

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

    float vertices[] = {
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };

    // VAO, VBO

    // Generate and Bind VAO to OpenGL Context.
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Gen and Bind VBO to GL_ARRAY_BUFFER
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // This line depends on the use case.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Upload index data to EBO.. (if using EBO)

    // glVertexAttribPointer...
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    //  0 - attrib location, in glsl: layout(location = 0) in vec3 position;
    // 3 - how many components per vertex(x,y,z) -> 3.
    // GL_FLOAT - type of the component.
    // GL_FALSE - don't normalize values.
    // 3 * sizeof(float) - how many bytes between consecutive vertices.
    // (void*)0 - offset, start reading the buffer from the beginning.
    glEnableVertexAttribArray(0); // Enable the attribute for the shaders.
    // Otherwise layout(location = 0) will have undefined data.
    glBindVertexArray(0); // Unbind VAO to stop editing it.

    // vertexShader, fragmentShader..
    const char *vertexSrc = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos, 1.0);
    }
    )";

    const char *fragmentSrc = R"(
    #version 330 core
    uniform vec3 myColor;
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(myColor, 1.0);
    }
    )";

    // Create and compile shaders.
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertexSrc, NULL);
    glCompileShader(vertShader);

    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentSrc, NULL);
    glCompileShader(fragShader);
    // Link shaders to program..
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    // Delete vertex shader and fragment shader once linked..
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    // Tell OpenGL to use the shader program;
    glUseProgram(shaderProgram);

    // Uniform locations..
    const int colorUniformLoc = glGetUniformLocation(shaderProgram, "myColor");
    glUniform3f(colorUniformLoc, 1.0f, 0.0f, 0.0f);

    // Main render loop.
    while (!glfwWindowShouldClose(window))
    {
        // Clear screen for next frame.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Input handling...
        handle_input(window);

        // Rendering commands...

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    (void)window; // Suppress unused parameter warning.
    (void)xpos;   // Remove cast to void if mouse input is needed in the future.
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