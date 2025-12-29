#include "Platform/OpenGL/OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Suki/Core/Assert.h"

namespace Suki
{

OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
{
    SK_ASSERT_MSG(m_Window, "Window pointer is null");
}

void OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_Window);
    int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SK_ASSERT_MSG(result, "Failed to load GLAD");
}

void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

}  // namespace Suki
