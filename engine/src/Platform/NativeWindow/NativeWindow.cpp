#include "Platform/NativeWindow/NativeWindow.h"
#include <GL/gl.h>
#include "GLFW/glfw3.h"
#include "Suki/Core/Logger.h"

namespace Suki
{

static uint8_t s_GLFWWindowCount = 0;

NativeWindow::NativeWindow(const WindowSpecs& specs)
{
    Init(specs);
}

NativeWindow::~NativeWindow()
{
    Shutdown();
}

void NativeWindow::Init(const WindowSpecs& specs)
{
    m_WindowSpecs.Title = specs.Title;
    m_WindowSpecs.Width = specs.Width;
    m_WindowSpecs.Height = specs.Height;

    SK_CORE_INFO("Initializing NativeWindow {0}", specs.Title);

    if(s_GLFWWindowCount == 0)
    {
        if(glfwInit())
            SK_CORE_INFO("GLFW Initialized");
        else
            SK_CRITICAL("GLFW Initialization Failed");
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    m_Window =
        glfwCreateWindow((int)m_WindowSpecs.Width, (int)m_WindowSpecs.Height,
                         m_WindowSpecs.Title.c_str(), NULL, NULL);
    s_GLFWWindowCount++;

    glfwMakeContextCurrent(m_Window);
}

void NativeWindow::Shutdown()
{

    glfwDestroyWindow(m_Window);
    s_GLFWWindowCount--;

    if(s_GLFWWindowCount == 0)
    {
        glfwTerminate();
    }
}

void NativeWindow::OnUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_Window);

    glfwPollEvents();
}

}  // namespace Suki
