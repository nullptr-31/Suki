#include "Platform/NativeWindow/NativeWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Suki/Core/Assert.h"
#include "Suki/Core/Logger.h"
#include "Suki/Event/ApplicationEvent.h"

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
    m_Data.Title = specs.Title;
    m_Data.Width = specs.Width;
    m_Data.Height = specs.Height;

    SK_CORE_INFO("Initializing NativeWindow {0}", specs.Title);

    if(s_GLFWWindowCount == 0)
    {
        int result = glfwInit();
        SK_ASSERT_MSG(result, "Failed to inialize GLFW");
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height,
                                m_Data.Title.c_str(), NULL, NULL);
    s_GLFWWindowCount++;

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(
        m_Window,
        [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_Window,
        [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });
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
    glfwPollEvents();

    m_Context->SwapBuffers();
}

}  // namespace Suki
